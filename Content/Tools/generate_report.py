import argparse
import csv
import os
import re
import sys
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Generate a visual report from a scan_results.csv produced by scan_assets.py"
    )
    parser.add_argument(
        "path", nargs="?", default=None,
        help="Path to the folder containing scan_results.csv, or to the csv "
             "file itself. If omitted the script searches from the current "
             "working directory."
    )
    return parser.parse_args()


SKIP_DIRS = {".git", "__pycache__", "node_modules", ".venv", "venv",
             "Binaries", "Intermediate", "Saved", "DerivedDataCache"}

def _search_for_csv(start: str) -> list[str]:
    """Recursively find all scan_results.csv files under start, skipping common noise dirs."""
    found = []
    for root, dirs, files in os.walk(start):
        dirs[:] = [d for d in dirs if d not in SKIP_DIRS and not d.startswith(".")]
        if "scan_results.csv" in files:
            found.append(root)
    return found


def resolve_scan_dir(user_path: str | None) -> str:
    """
    Return the directory that contains scan_results.csv.
    Raises SystemExit with a clear message if it cannot be found unambiguously.
    """
    if user_path:
        p = os.path.abspath(user_path)
        if os.path.isfile(p):
            if not p.endswith("scan_results.csv"):
                sys.exit(f"Error: expected a file named scan_results.csv, got: {p}")
            return os.path.dirname(p)
        if os.path.isdir(p):
            if os.path.exists(os.path.join(p, "scan_results.csv")):
                return p
            sys.exit(f"Error: scan_results.csv not found in: {p}")
        sys.exit(f"Error: path does not exist: {p}")

    cwd = os.getcwd()
    matches = _search_for_csv(cwd)

    if len(matches) == 1:
        return matches[0]

    if len(matches) == 0:
        sys.exit(
            f"Error: no scan_results.csv found under {cwd}\n"
            "Run scan_assets.py inside the UE5 editor first, then try again.\n"
            "Or pass the folder path explicitly: py generate_report.py <path>"
        )

    print("Multiple scan_results.csv files found. Please specify which to use:\n")
    for m in matches:
        print(f"  py generate_report.py \"{m}\"")
    sys.exit(1)


def load_csv(path: str) -> list[dict]:
    with open(path, newline="", encoding="utf-8") as f:
        return list(csv.DictReader(f))

def parse_size_mb(issue: str) -> float | None:
    match = re.match(r"([\d.]+)\s+MB", issue)
    return float(match.group(1)) if match else None

def parse_triangle_count(issue: str) -> int | None:
    match = re.match(r"([\d,]+)\s+triangles", issue)
    return int(match.group(1).replace(",", "")) if match else None

def parse_texture_dimensions(issue: str) -> tuple[int, int] | None:
    match = re.match(r"(\d+)x(\d+)px", issue)
    return (int(match.group(1)), int(match.group(2))) if match else None


def run_unit_tests(rows: list[dict]) -> bool:

    passed = 0
    failed = 0

    def check(condition: bool, label: str):
        nonlocal passed, failed
        if condition:
            print(f"  [PASS] {label}")
            passed += 1
        else:
            print(f"  [FAIL] {label}")
            failed += 1

    print("\n-- Unit Tests -------------------------------------------------------")

    check(len(rows) > 0, f"CSV is not empty ({len(rows)} rows loaded)")

    required = {"type", "name", "path", "issue"}
    check(all(required.issubset(r.keys()) for r in rows),
          "All rows contain required columns: type, name, path, issue")
    check(all(r["type"] and r["name"] and r["path"] and r["issue"] for r in rows),
          "No empty values in required fields")

    known_types = {"MESH", "TEXTURE", "LOD", "SIZE"}
    found_types = {r["type"] for r in rows}
    check(found_types.issubset(known_types),
          f"Only known issue types present: {found_types}")

    check(all("/" in r["path"] for r in rows),
          "All asset paths contain a '/' (look like UE5 content paths)")

    size_rows = [r for r in rows if r["type"] == "SIZE"]
    if size_rows:
        mbs = [parse_size_mb(r["issue"]) for r in size_rows]
        check(all(v is not None for v in mbs),
              f"All {len(size_rows)} SIZE issue strings parse to a float")
        check(all(v > 1.0 for v in mbs if v is not None),
              "All parsed SIZE values exceed the 1.0 MB limit")

    mesh_rows = [r for r in rows if r["type"] == "MESH"]
    if mesh_rows:
        tris = [parse_triangle_count(r["issue"]) for r in mesh_rows]
        check(all(v is not None for v in tris),
              f"All {len(mesh_rows)} MESH issue strings parse to an integer")
        check(all(v > 10_000 for v in tris if v is not None),
              "All parsed triangle counts exceed the 10,000 limit")

    tex_rows = [r for r in rows if r["type"] == "TEXTURE"]
    if tex_rows:
        dims = [parse_texture_dimensions(r["issue"]) for r in tex_rows]
        check(all(v is not None for v in dims),
              f"All {len(tex_rows)} TEXTURE issue strings parse to (width, height)")
        check(all(max(w, h) >= 2048 for w, h in dims if dims),
              "All parsed texture dimensions are at or above the 2048px limit")

    print(f"\n  {passed} passed, {failed} failed out of {passed + failed} assertions")
    return failed == 0


def generate_graph(rows: list[dict], output_path: str):
    type_colours = {
        "MESH":    "#e74c3c",
        "LOD":     "#e67e22",
        "SIZE":    "#f1c40f",
        "TEXTURE": "#3498db",
    }
    types = ["MESH", "LOD", "SIZE", "TEXTURE"]

    fig = plt.figure(figsize=(13, 9))
    fig.suptitle("Asset Scanner Results", fontsize=14, fontweight="bold", y=0.98)
    gs = gridspec.GridSpec(2, 2, figure=fig, hspace=0.5, wspace=0.38)

    ax1 = fig.add_subplot(gs[0, 0])
    counts = [sum(1 for r in rows if r["type"] == t) for t in types]
    bars = ax1.barh(types, counts, color=[type_colours[t] for t in types])
    ax1.bar_label(bars, padding=3, fontsize=9)
    ax1.set_xlabel("Issues Found")
    ax1.set_title("Issues by Type")
    ax1.set_xlim(0, max(counts) * 1.15)

    ax2 = fig.add_subplot(gs[0, 1])
    folders = sorted({r["path"] for r in rows})
    folder_labels = [p.split("/")[-1] for p in folders]
    bar_width = 0.35
    for fi, (folder, label) in enumerate(zip(folders, folder_labels)):
        folder_rows   = [r for r in rows if r["path"] == folder]
        folder_counts = [sum(1 for r in folder_rows if r["type"] == t) for t in types]
        offsets = [i + fi * bar_width for i in range(len(types))]
        ax2.bar(offsets, folder_counts, width=bar_width, label=label,
                color=[type_colours[t] for t in types],
                alpha=0.85 if fi == 0 else 0.55)
    ax2.set_xticks([i + bar_width / 2 for i in range(len(types))])
    ax2.set_xticklabels(types)
    ax2.set_ylabel("Issues Found")
    ax2.set_title("Issues by Type and Folder")
    ax2.legend(fontsize=8, title="Folder")

    size_data = sorted(
        [(r["name"], parse_size_mb(r["issue"])) for r in rows if r["type"] == "SIZE"],
        key=lambda x: x[1], reverse=True
    )
    ax3 = fig.add_subplot(gs[1, :])
    if size_data:
        names = [n[:30] + "..." if len(n) > 30 else n for n, _ in size_data]
        mbs   = [mb for _, mb in size_data]
        bar_colours = ["#e74c3c" if mb > 2.0 else "#e67e22" if mb > 1.5 else "#f1c40f"
                       for mb in mbs]
        bars3 = ax3.bar(range(len(names)), mbs, color=bar_colours)
        ax3.axhline(y=1.0, color="#2ecc71", linestyle="--", linewidth=1.5, label="1.0 MB limit")
        ax3.bar_label(bars3, labels=[f"{m:.2f}" for m in mbs], padding=2, fontsize=7.5)
        ax3.set_xticks(range(len(names)))
        ax3.set_xticklabels(names, rotation=35, ha="right", fontsize=7.5)
        ax3.set_ylabel("File Size (MB)")
        ax3.set_title("File Size Violations (assets over 1.0 MB limit)")
        ax3.legend(fontsize=9)
        ax3.set_ylim(0, max(mbs) * 1.18)
    else:
        ax3.text(0.5, 0.5, "No file size violations found",
                 ha="center", va="center", fontsize=12, color="grey")
        ax3.set_title("File Size Violations")
        ax3.axis("off")

    plt.savefig(output_path, dpi=150, bbox_inches="tight")
    plt.close()
    print(f"Graph saved     : {output_path}")

def extract_header_block(md_path: str) -> str | None:
    """
    Return everything up to and including the --- after the Summary table.
    Returns None if the markdown doesn't exist or has no Summary table yet.
    """
    if not os.path.exists(md_path):
        return None
    with open(md_path, "r", encoding="utf-8") as f:
        content = f.read()
    match = re.search(r"^.*?\*\*Total\*\*[^\n]*\n\n---\n", content, re.DOTALL)
    return match.group(0) if match else None


def build_issue_table(rows: list[dict]) -> list[str]:
    lines = ["| Asset Name | Content Path | Issue |", "|---|---|---|"]
    for r in rows:
        lines.append(f"| `{r['name']}` | `{r['path']}` | {r['issue']} |")
    return lines


def rebuild_markdown(rows: list[dict], header_block: str, png_filename: str) -> str:
    """
    Reconstruct scan_results.md cleanly each time:
      header_block  -- preserved from original (scan timestamp + summary counts)
      ## Graphs     -- embedded chart image
      ## Triangle Count Issues
      ## Texture Size Issues
      ## LOD Issues
      ## Asset File Size Issues
    """
    meshes   = [r for r in rows if r["type"] == "MESH"]
    textures = [r for r in rows if r["type"] == "TEXTURE"]
    lods     = [r for r in rows if r["type"] == "LOD"]
    sizes    = [r for r in rows if r["type"] == "SIZE"]

    lines = [header_block.rstrip("\n")]
    lines.append("\n## Graphs\n")
    lines.append(f"![Issue Breakdown]({png_filename})\n")

    for section_name, section_rows in [
        ("Triangle Count Issues", meshes),
        ("Texture Size Issues",   textures),
        ("LOD Issues",            lods),
        ("Asset File Size Issues", sizes),
    ]:
        if section_rows:
            lines.append("\n---\n")
            lines.append(f"## {section_name}\n")
            lines.extend(build_issue_table(section_rows))

    lines.append("\n---\n")
    return "\n".join(lines)


if __name__ == "__main__":
    args = parse_args()
    scan_dir = resolve_scan_dir(args.path)

    csv_path = os.path.join(scan_dir, "scan_results.csv")
    md_path  = os.path.join(scan_dir, "scan_results.md")
    png_path = os.path.join(scan_dir, "scan_results.png")

    print(f"Scan folder     : {scan_dir}")
    print(f"Loading CSV     : {csv_path}")
    rows = load_csv(csv_path)
    print(f"Loaded {len(rows)} rows.")

    all_passed = run_unit_tests(rows)
    if not all_passed:
        print("\nWarning: some tests failed. Report will still be generated.")

    print("\nGenerating graph...")
    generate_graph(rows, png_path)

    print("Rebuilding markdown...")
    header = extract_header_block(md_path)
    if header is None:
        sys.exit(
            f"Error: could not find scan_results.md (or its Summary table) in {scan_dir}\n"
            "Make sure scan_assets.py has been run inside UE5 first."
        )
    new_md = rebuild_markdown(rows, header, "scan_results.png")
    with open(md_path, "w", encoding="utf-8") as f:
        f.write(new_md)
    print(f"Markdown saved  : {md_path}")

    print("\nDone. Open scan_results.md to see the full report.")
