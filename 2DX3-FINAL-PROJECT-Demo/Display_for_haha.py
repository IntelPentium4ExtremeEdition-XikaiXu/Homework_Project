import numpy as np
import open3d as o3d

def group_points_by_x(pcd):
    # Group points by their x-values
    grouped_points = {}
    for i, point in enumerate(np.asarray(pcd.points)):
        x = round(point[0], 5)  # Round x to handle floating point imprecision
        if x not in grouped_points:
            grouped_points[x] = []
        grouped_points[x].append(i)
    return grouped_points

def connect_adjacent_points(pcd, indices):
    # Generate lines connecting adjacent points in the set of indices
    lines = []
    sorted_indices = sorted(indices)  # Sort indices to ensure adjacent points are connected
    for i in range(len(sorted_indices) - 1):
        lines.append([sorted_indices[i], sorted_indices[i + 1]])
    return lines

def connect_adjacent_planes(grouped_points):
    # Generate lines connecting adjacent points between neighboring x-planes
    lines = []
    x_values = sorted(grouped_points.keys())
    for i in range(len(x_values) - 1):
        x1, x2 = x_values[i], x_values[i + 1]
        points1 = grouped_points[x1]
        points2 = grouped_points[x2]
        for j in range(len(points1)):
            lines.append([points1[j], points2[j]])
    return lines

def main():
    # Read the test data from the file we created
    print("Read in the prism point cloud data (pcd)")
    pcd = o3d.io.read_point_cloud("haha.xyz", format="xyz")

    # Group points by their x-values
    grouped_points = group_points_by_x(pcd)

    # Generate lines connecting adjacent points for each group of points
    lines = []
    for x, indices in grouped_points.items():
        lines.extend(connect_adjacent_points(pcd, indices))

    # Generate lines connecting adjacent points between neighboring x-planes
    lines.extend(connect_adjacent_planes(grouped_points))

    # Create LineSet
    line_set = o3d.geometry.LineSet()
    line_set.points = o3d.utility.Vector3dVector(np.asarray(pcd.points))
    line_set.lines = o3d.utility.Vector2iVector(lines)

    # Visualize the point cloud and the lines
    o3d.visualization.draw_geometries([pcd, line_set])

if __name__ == "__main__":
    main()
