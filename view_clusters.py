import pandas as pd
import open3d as o3d
import numpy as np
import matplotlib.pyplot as plt

df_Raw_Point_Cloud = pd.read_csv("Point_Cloud_1.1_clusters.csv", skiprows=2, header=None)
df_Raw_Point_Cloud.columns = ['x', 'y', 'z', 'cluster']

# Build point array
points = np.vstack((df_Raw_Point_Cloud['x'], df_Raw_Point_Cloud['y'], df_Raw_Point_Cloud['z'])).T

# Color each cluster
cluster_ids = df_Raw_Point_Cloud['cluster'].unique()
cmap = plt.get_cmap("tab20", len(cluster_ids))
cluster_to_color = {cid: cmap(i)[:3] for i, cid in enumerate(cluster_ids)}
colors = np.array([cluster_to_color[c] for c in df_Raw_Point_Cloud['cluster']])

# Create and visualize point cloud
pcd = o3d.geometry.PointCloud()
pcd.points = o3d.utility.Vector3dVector(points)
pcd.colors = o3d.utility.Vector3dVector(colors)
o3d.visualization.draw_geometries([pcd])
