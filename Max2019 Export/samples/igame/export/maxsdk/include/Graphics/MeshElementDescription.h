//
// Copyright 2011 Autodesk, Inc.  All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which 
// otherwise accompanies this software in either electronic or hard copy form.   
//
//

#pragma once

#include "../MaxHeap.h"
#include "GraphicsExport.h"

namespace MaxSDK { namespace Graphics {

/** This enum describes the type of mesh element to be generated. Each mesh element 
	corresponds to a specific render item generated by calling Mesh::GenerateRenderItems()
	or MNMesh::GenerateRenderItems().
*/
enum MeshElementType
{
	/** Solid Mesh, it could be: vertex color mesh or general mesh. This will 
	be displayed in any viewport that requires smooth mesh.
	*/
	MeshElementTypeSolidMesh,
	/** Vertex ticks. This will be displayed when the node has "Vertex Ticks" 
	display option on or the vertex tick sub-object be selected.
	*/
	MeshElementTypeVertexTicks,
	/** Edge mesh, this layer includes the edges. This will be displayed in 
	viewport that has "wireframe" or "hidden line" on or when the edge sub-object
	level is selected. 
	*/
	MeshElementTypeEdge,
	/** Diagonal Mesh. This is the dotted edge lines when user turn off "edges 
	only" display property of a node and enable the wireframe mode of viewport.
	*/
	MeshElementTypeDiagonal, 
	/** Face Mesh. This is the face render item of the mesh when this mesh is 
	displayed in face sub-object level.
	*/
	MeshElementTypeFace,
	/** Mesh normals. This mesh element is required when we need to show all normals
	of selected face.
	*/
	MeshElementTypeNormal
};

/** When a mesh is displayed in any sub-object level, this enum help decide which
part of the mesh this mesh element belongs to. 
*/
enum MeshPart
{
	/** Selected part. Only the selected part of the mesh will be displayed. 
	\remarks For an edge/diagonal/face mesh element, this value indicates that the mesh
			element only includes the selected edges/diagonals/faces of the mesh.
			For a vertex ticks mesh element, it will include the whole of the mesh. 
			But selected vertices will be displayed in red(indicating they're selected).
	*/
	MeshPartSelected,
	/** Unselected part. Only the unselected part of the mesh will be displayed. 
	\remarks For an edge/diagonal/face mesh element, this value indicates that the render 
			item only include the unselected edges/diagonals/faces of the mesh.
			For a vertex ticks mesh element, it will include the whole of the mesh. 
			But selected vertices won't be displayed in red.
	*/
	MeshPartUnselected,
	/** Whole part. This value indicates an render item includes the whole of the mesh.
	*/
	MeshPartWhole
};

/** This class describes a single mesh element(which corresponds to a render item)
required to be generated by calling	Mesh::GenerateRenderItems() or MNMesh::GenerateRenderItems()
from the specified mesh(or mnmesh).
*/
class MeshElementDescription : public MaxHeapOperators
{
public:
	GraphicsDriverAPI MeshElementDescription();
	GraphicsDriverAPI MeshElementDescription(unsigned long descriptionBits);
	GraphicsDriverAPI ~MeshElementDescription();
	GraphicsDriverAPI MeshElementDescription(const MeshElementDescription& from);
	GraphicsDriverAPI MeshElementDescription& operator = (const MeshElementDescription& from);

	/** Get the type of this mesh element.
	\return the mesh element type. 
	*/
	GraphicsDriverAPI MeshElementType GetMeshElementType() const;
	/** Set the type of this mesh element.
	\param type The specified mesh element type.
	*/
	GraphicsDriverAPI void SetMeshElementType(MeshElementType type);

	/** Get the part of this mesh element.
	\return the mesh part. 
	*/
	GraphicsDriverAPI MeshPart GetMeshPart() const;
	/** Set the part of this mesh element.
	\param meshPart The specified mesh part.
	*/
	GraphicsDriverAPI void SetMeshPart(MeshPart meshPart);

	/** Specify whether to shade the mesh element in soft selection color. Turn on 
	this option when an mesh element is displayed in any sub-object level using soft
	selection
	\param onOff True to enable and false to disable.
	\remark this option has no effect an a mesh element whose MeshPart is MeshPartSelected.
		The selected edge/diagonal/face mesh element will always be shaded in red. 
		For the vertex ticks mesh element, when this option "on" its selected vertices 
		will be displayed in red while the unselected ones will be shaded in soft 
		selection color. And when "off", all vertices will be shaded in soft selection
		color.
	*/
	GraphicsDriverAPI void SetUseSoftSelectionColor(bool onOff);
	/** Get whether to shade the mesh element in soft selection color. 
	\return true if shaded in soft selection color or false otherwise.
	*/
	GraphicsDriverAPI bool GetUseSoftSelectionColor() const;

	/** Get whether the mesh element requires its back faces to be culled.
	\return whether to cull the back face. 
	*/
	GraphicsDriverAPI bool GetBackfaceCull() const;
	/** Specify whether the mesh element requires its back faces to be culled.
		\param onOff whether to cull the back face.
	*/
	GraphicsDriverAPI void SetBackfaceCull(bool onOff);

	/** Get the description bits of this element description. This value is a 
		combination of all member values on bit base and corresponds to a specific
		type of mesh element description. Developers may use it to query a render 
		item from an IRenderItemContainer.
		\return the description bits corresponding to this element description
	*/
	GraphicsDriverAPI unsigned long GetDescriptionBits() const;

private:
	MeshElementType mMeshElementType;
	MeshPart mMeshPart;
	bool mbUseSoftSelection;
	bool mbBackfaceCull;
};

/** This enum defines some kinds of built-in mesh element descriptions. Developer 
		may query a built-in mesh element description by calling
		MeshElementDescription::GetBuiltInMeshElementDescription() using any enum value below.
*/
enum BuiltInMeshElementDescription
{
	/** The mesh element description of a solid mesh.
		MeshElementType : MeshElementTypeSolidMesh
		MeshPart : MeshPartWhole
		UseSoftSelectionColor : false
		BackfaceCull : false
	*/
	ElementDescriptionSolidMesh,

	/** The mesh element description of vertex ticks.
		MeshElementType : MeshElementTypeVertexTicks
		MeshPart : MeshPartWhole
		UseSoftSelectionColor : false
		BackfaceCull : false
	*/
	ElementDescriptionVetexTicks,

	/** The mesh element description of a wireframe mesh.
		MeshElementType : MeshElementTypeEdge
		MeshPart : MeshPartWhole
		UseSoftSelectionColor : false
		BackfaceCull : false
	*/
	ElementDescriptionWireframe,

	/** The mesh element description of selected edges.
		MeshElementType : MeshElementTypeEdge
		MeshPart : MeshPartSelected
		UseSoftSelectionColor : false
		BackfaceCull : false
	*/
	ElementDescriptionSelectedEdge,

	/** The mesh element description of diagonals.
		MeshElementType : MeshElementTypeDiagonal
		MeshPart : MeshPartWhole
		UseSoftSelectionColor : false
		BackfaceCull : false
	*/
	ElementDescriptionDiagonal,

	/** The mesh element description of selected diagonals.
		MeshElementType : MeshElementTypeDiagonal
		MeshPart : MeshPartSelected
		UseSoftSelectionColor : false
		BackfaceCull : false
	*/
	ElementDescriptionSelectedDiagonal,

	/** The mesh element description of selected faces.
		MeshElementType : MeshElementTypeFace
		MeshPart : MeshPartSelected
		UseSoftSelectionColor : false
		BackfaceCull : false
	*/
	ElementDescriptionSelectedFace
};

/** Get a specified built-in mesh element description.
	\param type the kind of built-in mesh element description
	\return the specified mesh element description.
*/
GraphicsDriverAPI const MeshElementDescription& GetBuiltInMeshElementDescription(
	BuiltInMeshElementDescription type);

} } // namespace
