import unreal
import csv
import os
from datetime import datetime

MAX_TRIANGLES = 50000
MAX_TEXTURE_SIZE = 4096
MIN_LODS = 2
SCAN_PATH = "/All/Game/DropOff"

def scan_meshes():
    flagged = []
    asset_registry = unreal.AssetRegistryHelpers.get_asset_registry()

    mesh_class_path = unreal.TopLevelAssetPath("/Script/Engine", "StaticMesh")
    mesh_assets = asset_registry.get_assets_by_class(mesh_class_path)

    for asset_data in mesh_assets:
        if not str(asset_data.package_path).startswith(SCAN_PATH):
            continue

        mesh = unreal.EditorAssetLibrary.load_asset(str(asset_data.object_path))
        if not isinstance(mesh, unreal.StaticMesh):
            continue

        triangle_count = mesh.get_num_triangles(0)
        if triangle_count > MAX_TRIANGLES:
            flagged.append({
                "type": "MESH",
                "name": str(asset_data.asset_name),
                "path": str(asset_data.package_path),
                "issue": f"{triangle_count:,} triangles (limit: {MAX_TRIANGLES:,})"
            })

        lod_count = mesh.get_num_lods()
        if lod_count < MIN_LODS:
            flagged.append({
                "type": "LOD",
                "name": str(asset_data.asset_name),
                "path": str(asset_data.package_path),
                "issue": f"Only {lod_count} LOD level(s) found (minimum recommended: {MIN_LODS})"
            })

    return flagged

def scan_textures():
    flagged = []
    asset_registry = unreal.AssetRegistryHelpers.get_asset_registry()

    texture_class_path = unreal.TopLevelAssetPath("/Script/Engine", "Texture2D")
    texture_assets = asset_registry.get_assets_by_class(texture_class_path)

    for asset_data in texture_assets:
        if not str(asset_data.package_path).startswith(SCAN_PATH):
            continue

        texture = unreal.EditorAssetLibrary.load_asset(str(asset_data.object_path))
        if not isinstance(texture, unreal.Texture2D):
            continue

        width = texture.blueprint_get_size_x()
        height = texture.blueprint_get_size_y()

        if width >= MAX_TEXTURE_SIZE or height >= MAX_TEXTURE_SIZE:
            flagged.append({
                "type": "TEXTURE",
                "name": str(asset_data.asset_name),
                "path": str(asset_data.package_path),
                "issue": f"{width}x{height}px (limit: {MAX_TEXTURE_SIZE}px)"
            })

    return flagged

# Markdown file creator
def generate_markdown(flagged_assets, script_dir):
    meshes   = [a for a in flagged_assets if a["type"] == "MESH"]
    textures = [a for a in flagged_assets if a["type"] == "TEXTURE"]
    lods     = [a for a in flagged_assets if a["type"] == "LOD"]

    total = len(flagged_assets)
    timestamp = datetime.now().strftime("%d/%m/%Y at %H:%M")

    lines = []

    lines.append("# UE5 Optimisation Scan Report")
    lines.append(f"\n> Scanned on {timestamp}  ")
    lines.append(f"> Scan path: `{SCAN_PATH}`  ")
    lines.append(f"> Thresholds: `{MAX_TRIANGLES:,}` triangles · `{MAX_TEXTURE_SIZE}px` textures · `{MIN_LODS}` minimum LODs")

    lines.append("\n---\n")
    lines.append("## Summary\n")
    lines.append("| Category | Issues Found |")
    lines.append("|---|---|")
    lines.append(f"| Meshes over triangle limit | {len(meshes)} |")
    lines.append(f"| Textures at 4K or above | {len(textures)} |")
    lines.append(f"| Meshes missing LODs | {len(lods)} |")
    lines.append(f"| **Total** | **{total}** |")

    if total == 0:
        lines.append("\n **No issues found! Project looks optimised.**")

    if meshes:
        lines.append("\n---\n")
        lines.append("## Triangle Count Issues\n")
        lines.append("| Asset Name | Content Path | Issue |")
        lines.append("|---|---|---|")
        for a in meshes:
            lines.append(f"| `{a['name']}` | `{a['path']}` | {a['issue']} |")

    if textures:
        lines.append("\n---\n")
        lines.append("## Texture Size Issues\n")
        lines.append("| Asset Name | Content Path | Issue |")
        lines.append("|---|---|---|")
        for a in textures:
            lines.append(f"| `{a['name']}` | `{a['path']}` | {a['issue']} |")

    if lods:
        lines.append("\n---\n")
        lines.append("## LOD Issues\n")
        lines.append("| Asset Name | Content Path | Issue |")
        lines.append("|---|---|---|")
        for a in lods:
            lines.append(f"| `{a['name']}` | `{a['path']}` | {a['issue']} |")


    md_path = os.path.join(script_dir, "scan_results.md")
    with open(md_path, "w", encoding="utf-8") as f:
        f.write("\n".join(lines))

    return md_path

def print_and_export(flagged_assets):
    print("\n========== OPTIMISATION SCAN RESULTS ==========")

    if not flagged_assets:
        print("No issues found! Project looks optimised.")
    else:
        meshes   = [a for a in flagged_assets if a["type"] == "MESH"]
        textures = [a for a in flagged_assets if a["type"] == "TEXTURE"]
        lods     = [a for a in flagged_assets if a["type"] == "LOD"]

        print(f"Found {len(flagged_assets)} issue(s) across the project:\n")
        print(f"  Meshes over triangle limit : {len(meshes)}")
        print(f"  Textures at 4K or above    : {len(textures)}")
        print(f"  Meshes missing LODs        : {len(lods)}")
        print()

        if meshes:
            print("--- TRIANGLE COUNT ISSUES ---")
            for asset in meshes:
                print(f"  [{asset['name']}]")
                print(f"    Path : {asset['path']}")
                print(f"    Issue: {asset['issue']}")
            print()

        if textures:
            print("--- TEXTURE SIZE ISSUES ---")
            for asset in textures:
                print(f"  [{asset['name']}]")
                print(f"    Path : {asset['path']}")
                print(f"    Issue: {asset['issue']}")
            print()

        if lods:
            print("--- LOD ISSUES ---")
            for asset in lods:
                print(f"  [{asset['name']}]")
                print(f"    Path : {asset['path']}")
                print(f"    Issue: {asset['issue']}")
            print()

    script_dir = os.path.dirname(os.path.abspath(__file__))

    csv_path = os.path.join(script_dir, "scan_results.csv")
    with open(csv_path, "w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=["type", "name", "path", "issue"])
        writer.writeheader()
        writer.writerows(flagged_assets)

    md_path = generate_markdown(flagged_assets, script_dir)

    print(f"CSV saved to     : {csv_path}")
    print(f"Report saved to  : {md_path}")

all_flagged = scan_meshes() + scan_textures()
print_and_export(all_flagged)