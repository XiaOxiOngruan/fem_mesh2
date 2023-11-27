# fem_mesh2
Finite Element Tetrahedral Mesh Refinement (Adaptive Refinement)
# Program Description
Run the fem_mesh.exe program to execute the refinement program.

This program implements adaptive refinement for a subset of tetrahedral elements and requires input files in .xyz and .lv formats. The .xyz file stores the coordinates of points, with the first line indicating the total number of points. The .lv file stores the global numbering information of points on tetrahedral elements (arranged by local numbering), with the first line indicating the total number of tetrahedral elements.

The program refines the edges of tetrahedra, requiring input from .le and .re files. The .le file stores the global numbering of the six edges of each tetrahedron. The .re file stores the error magnitudes for each edge and is sorted in descending order.

After the program finishes running, it outputs two new files: .xyz and .lv.

# Explanation of Global Numbering for Nodes and Edges on Elements
The local numbering of nodes on an element follows the right-hand rule.

After refinement, the global numbering of the new edges on the elements needs to be reorganized.

The local numbering of edges on a tetrahedron is as follows, where the left side represents the local edge number, and the right side represents the local node numbers of the connected points:

Edge 1: (1, 2)
Edge 2: (1, 3)
Edge 3: (1, 4)
Edge 4: (2, 3)
Edge 5: (2, 4)
Edge 6: (3, 4)
# Explanation of the Refinement Algorithm
Read the mesh geometry refinement information.
Iterate through all elements.
Traverse all edges of the current element and determine whether refinement is necessary.
If a certain edge needs refinement, generate a new midpoint (no need to generate if the midpoint already exists).
Generate a new element and modify the numbering of the old element.
Continue iterating through all elements until the traversal is complete.
