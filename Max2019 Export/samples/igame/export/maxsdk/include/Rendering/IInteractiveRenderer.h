//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include "../BaseInterface.h"
#include "../actiontableTypedefs.h"
#include "RendProgressCallback.h"

class IIRenderMgr;
class Bitmap;
class INode;
class ViewExp;
class Box2;
class DefaultLight;
class ActionCallback;
class Color;

/*! \sa  Class InterfaceServer, Class IIRenderMgr, Class INode, Class ViewExp, Class Bitmap, Class DefaultLight, Class IRenderProgressCallback,  Class Animatable,  Class ActionTable\n\n
\par Description:
This is the abstract class (Interface) for a a renderer supporting interactive
rendering.\n\n
With the likelihood of evolving rendering and shading techniques which are
going to be markedly different from what is being used now, the 3ds Max SDK
provides the infrastructure to support interactive rendering. Since renderers
are a plugin to 3ds Max and since each renderer has a different set of
resources and capabilities the interactive rendering and shading API has been
made as general and independent as possible. The independence of the renderer
also means that the renderer must do a fair amount of work that could be done
by the system for all renderers.\n\n
Interactive rendering and shading is a separate interface which can be
optionally supported by 3rd party renderers and can be obtained by using the
<b>GetInterface()</b> method on the renderer. <b>I_RENDER_ID</b> is passed as
the ID parameter to a renderer's implementation of
<b>Animatable::GetInterface()</b>. The renderer returns a pointer to a class
<b>IInteractiveRender</b> instance if it supports interactive rendering,
otherwise the default implementation will return NULL, indicating that
interactive rendering is not supported. This class, <b>IInteractiveRender</b>
is defined in <b>/MAXSDK/INCLUDE/interactiveRendering.h</b>.\n\n
As it is, interactive renderers will reference any and all objects, as well as
lights and materials in the scene that they can respond to changes from. Via
the normal 3ds Max notification system the interactive shader will then receive
messages whenever one of these referenced objects changes and it must then
decide how best to update the scene for the user.  */
class IInteractiveRender : public InterfaceServer
{
public:

    class IProgressCallback;

	// notification of begin and end of interactive rendering
	/*! \remarks This method initiates the interactive rendering and will
	reference objects in the scene so the renderer receives the proper change
	notifications. The interactive renderer will automatically update the scene
	when these changes are received.\n\n
	This is called when the user first invokes interactive rendering. During
	the begin session call, the renderer should reference any object in the
	scene that it can respond to changes from. There are reference manager
	classes in the SDK to ease this referencing in the file
	<b>referenceManager.h</b>. many of the parameters of interactive reshading
	are set up prior to the call to <b>BeginSession()</b>, here is a code
	snippet from the interactive rendering manager:\n\n
	<b>mIRenderInterface-\>SetOwnerWnd(mpIMaxBitmapViewer-\>GetHDisplayWindow());</b>\n\n
	<b>mIRenderInterface-\>SetIIRenderMgr(this);</b>\n\n
	<b>mIRenderInterface-\>SetBitmap(mpIMaxBitmapViewer-\>GetBitmap());</b>\n\n
	<b>mIRenderInterface-\>SetSceneINode(mpInterface-\>GetRootNode());</b>\n\n
	<b>mIRenderInterface-\>SetUseViewINode(false);</b>\n\n
	<b>mIRenderInterface-\>SetViewINode(NULL);</b>\n\n
	<b>mIRenderInterface-\>SetViewExp(mpViewExp);</b>\n\n
	<b>mIRenderInterface-\>SetRegion(mSelectedRegion);</b>\n\n
	<b>mIRenderInterface-\>SetDefaultLights(mDefaultLights,
	mNumDefaultLights);</b>\n\n
	<b>mIRenderInterface-\>SetProgressCallback(</b>\n\n
	<b>dynamic_cast\<IProgressCallback *\>(\&mImageViewerCB)</b>\n\n
	<b>);</b>\n\n
	<b>mIRenderInterface-\>BeginSession();</b>\n\n
	Consequently, <b>BeginSession()</b> can rely on all these local attributes
	being valid. */
	virtual void BeginSession() = 0;
	/*! \remarks This method will end an interactive rendering session and
	will remove all references placed on the scene. */
	virtual void EndSession() = 0;

	// sets/gets the owner window (to be passed to renderer, if necessary)
	/*! \remarks This method allows you to set the owner window, which could
	come in handy if you want to pass it to the renderer if necessary. The
	owner HWND is supplied to the interactive renderer so that it may receive
	window messages for the interactive window, update the window, etc.
	\par Parameters:
	<b>HWND hOwnerWnd</b>\n\n
	A handle to the owner window. */
	virtual void SetOwnerWnd(HWND hOwnerWnd) = 0;
	/*! \remarks This method allows you to retrieve the owner window. */
	virtual HWND GetOwnerWnd() const = 0;

	// sets/gets the pointer to the interactive rendering manager
	/*! \remarks This method sets a pointer to the controlling renderMgr, so
	that various states can be queried.
	\par Parameters:
	<b>IIRenderMgr *pIIRenderMgr</b>\n\n
	A pointer to the controlling interactive rendering manager. */
	virtual void SetIIRenderMgr(IIRenderMgr *pIIRenderMgr) = 0;
	/*! \remarks This method allows you to retrieve a pointer to the
	controlling interactive render manager
	\par Parameters:
	<b>IIRenderMgr *pIIRenderMgr</b>\n\n
	A pointer to the render manager interface.\n\n
	Used internally. This should always be set to NULL. */
	virtual IIRenderMgr *GetIIRenderMgr(IIRenderMgr *pIIRenderMgr) const = 0;

	// sets/gets the bitmap to be rendered to
	/*! \remarks This method allows you to set the destination bitmap to be
	rendered and re-rendered to. This destination bitmap is persistent between
	update renderings, basically the renderer holds the bitmap and updates the
	screen while the manager holds the reference to the bitmap and controls its
	lifetime.
	\par Parameters:
	<b>Bitmap *pDestBitmap</b>\n\n
	A pointer to the destination bitmap to set. */
	virtual void SetBitmap(Bitmap *pDestBitmap) = 0;
	/*! \remarks This method allows you to retrieve the destination bitmap
	that's being redered and re-rendered to.
	\par Parameters:
	<b>Bitmap *pDestBitmap</b>\n\n
	A pointer to the destination bitmap.\n\n
	Used internally. This should always be set to NULL. */
	virtual Bitmap *GetBitmap(Bitmap *pDestBitmap) const = 0;

	// sets/gets the scene root node
	/*! \remarks This method allows you to set the scene root node. In
	general, the idea of interactive rendering is to start with a fixed scene
	and then respond to changes in that scene. This call sets the scene root
	node. All items stemming from this scene root that an interactive renderer
	can respond to changes in should be referenced.
	\par Parameters:
	<b>INode *pSceneINode</b>\n\n
	A pointer to the scene root node. */
	virtual void SetSceneINode(INode *pSceneINode) = 0;
	/*! \remarks This method returns a pointer to the scene's root node. */
	virtual INode *GetSceneINode() const = 0;

	// sets/gets whether to use the ViewINode. if false, ViewParams should be used
	/*! \remarks This method sets whether to use the ViewINode. When a
	separate camera node is needed instead of ViewExp, the interactive
	rendering manager will set the viewINode to the interactive renderer and
	set UseViewINode to TRUE.
	\par Parameters:
	<b>bool bUseViewINode</b>\n\n
	If FALSE, ViewParams obtained from ViewExp should be used. */
	virtual void SetUseViewINode(bool bUseViewINode) = 0;
	/*! \remarks This method returns FALSE if the ViewParams obtained from
	ViewExp should be used. TRUE would indicate that this is not the case. */
	virtual bool GetUseViewINode() const = 0;

	// sets/gets the ViewINode
	/*! \remarks This method allows you to set the View INode in case a
	separate camera node is needed instead of ViewExp.
	\par Parameters:
	<b>INode *pViewINode</b>\n\n
	A pointer to the view node. */
	virtual void SetViewINode(INode *pViewINode) = 0;
	/*! \remarks This method returns a pointer to the view node if this is
	used instead of ViewExp. */
	virtual INode *GetViewINode() const = 0;

	// sets/gets the ViewExp
	/*! \remarks This method allows you to set the ViewExp. The ViewExp is the
	view specification for docked windows. The interactive renderer gets the
	view params out of the ViewExp.
	\par Parameters:
	<b>ViewExp *pViewExp</b>\n\n
	A pointer to the ViewExp. */
	virtual void SetViewExp(ViewExp *pViewExp) = 0;
	/*! \remarks This method returns a pointer to the ViewExp which is used
	for the view specification for docked windows. */
	virtual ViewExp *GetViewExp() const = 0;

	// sets/gets the region of the bitmap to be rendered. if Box2::IsEmpty() returns true, it indicates to render entire bitmap
	/*! \remarks This method allows you to set the region of the bitmap to be
	rendered.\n\n
	There are two standard interactive modes that should be supported in all
	interactive renderers: region rendering and selected object rendering, and
	these modes should ideally work in consort if at all possible: scenes are
	often very complex and the plugin renderer must be able to limit complexity
	to increase interactivity. Note that if <b>Box2::IsEmpty()</b> returns
	TRUE, it indicates to render entire bitmap.
	\par Parameters:
	<b>const Box2 \&region</b>\n\n
	A reference to the rectangular area. */
	virtual void SetRegion(const Box2 &region) = 0;
	/*! \remarks This method returns the region of the bitmap to be rendered.
	Note that if <b>Box2::IsEmpty()</b> returns TRUE, it indicates to render
	entire bitmap. */
	virtual const Box2 &GetRegion() const = 0;

	// sets/gets the lights to be used in abscence of scene lights
	/*! \remarks This method allows you to set the default lights to be used
	in absence of scene lights. These lights will be used when no user
	specified lights are in the scene. This should be noted when the scene is
	traversed in begin session, and of course altered if new user lights are
	created.
	\par Parameters:
	<b>DefaultLight *pDefLights</b>\n\n
	A pointer to a default light source.\n\n
	<b>int numDefLights</b>\n\n
	The number of default lights. */
	virtual void SetDefaultLights(DefaultLight *pDefLights, int numDefLights) = 0;
	/*! \remarks This method returns a pointer to the default lights and the
	number of default lights which are used in absence of scene lights.
	\par Parameters:
	<b>int \&numDefLights</b>\n\n
	The number of default lights returned. */
	virtual const DefaultLight *GetDefaultLights(int &numDefLights) const = 0;

	// sets/gets the pointer to progress callback object
	/*! \remarks This method allows you to set an interactive rendering
	progress callback object.\n\n
	The Progress/Abort Callback should be called by the renderer ideally about
	every 100 milliseconds, but the actual range varies widely. The callback
	allows the manager to display rendering progress and/or abort a rendering.
	\par Parameters:
	<b>IProgressCallback *pProgCB</b>\n\n
	A pointer to the interactive rendering progress callback object. */
	virtual void SetProgressCallback(IProgressCallback *pProgCB) = 0;
	/*! \remarks This method returns a pointer to the interactive rendering
	progress callback object. */
	virtual const IProgressCallback *GetProgressCallback() const = 0;

	// renders the bitmap using default rendering functionality
	/*! \remarks This method renders the bitmap using default non-interactive
	rendering functionality. This is the only actual command to the interactive
	renderer.
	\par Parameters:
	<b>Bitmap *pDestBitmap</b>\n\n
	The destination bitmap to render to. */
	virtual void Render(Bitmap *pDestBitmap) = 0;

	// returns the NodeRenderID for a given bitmap pixel location
	// Return 0 if there is no node
	/*! \remarks This method returns the closest node handle for a given
	bitmap pixel location. This can be implemented with an item buffer, by
	using ray casting, or some other method and allows the interactive
	rendering manager to implement object selection.
	\par Parameters:
	<b>int x, int y</b>\n\n
	The x and y coordinate of the bitmap pixel.
	\return  The node handle or 0 if there is no node. */
	virtual ULONG GetNodeHandle(int x, int y) = 0;

	// fills the sBBox parameter with the screen space bounding box for a given INode. returns true if successful, otherwise false.
	/*! \remarks This method returns the screen bounding box of the
	corresponding INode, so the selection box corners can be drawn.
	\par Parameters:
	<b>Box2\& sBBox</b>\n\n
	The screen bounding box.\n\n
	<b>INode *pINode</b>\n\n
	The INode for which you wish to retrieve the screen bounding box.
	\return  TRUE if successful, otherwise FALSE. */
	virtual bool GetScreenBBox(Box2& sBBox, INode *pINode) = 0;

	// returns ActionTableId for any action items the reshading renderer may implement. returns 0 if none.
	/*! \remarks This method returns the ActionTableId for any action items
	the renderer may implement. This method will return 0 if none are
	available. Action tables are used as context sensitive command system to
	generate quad menus and the like from the various objects in the scene. */
	virtual ActionTableId GetActionTableId() = 0;

	// returns ActionCallback for any action items the reshading renderer may implement. returns NULL if none.
	/*! \remarks This method returns a pointer to an ActionCallback for any
	action items the renderer may implement. This method will return NULL if
	none are available. */
	virtual ActionCallback *GetActionCallback() = 0;

	// access to additional method interfaces
	/*! \remarks This method provides a general extension mechanism, access to
	additional method interfaces.
	\par Default Implementation:
	<b>{ return NULL; }</b> */
	virtual void *GetInterface() { return NULL; }

	// find out if the renderer is currently rendering
	/*! \remarks This method returns TRUE if the renderer is currently
	rendering, otherwise FALSE.\n\n
	When the interactive rendering manager gets a message to shut down or abort
	an interactive rendering, there is a potential race condition between the
	interactive renderer shutting down and the shutting down of the manager
	itself, which deletes the renderer. Since it is the renderer itself that
	decides when, what and how to re-render the image, it's not clear to the
	manager whether a delete is safe. This method allows the manager to inquire
	whether the renderer is recomputing the image. To abort a rendering, the
	progress/abort callback must be used. When the abort is complete,
	IsRendering will return FALSE. */
	virtual BOOL IsRendering() = 0;

	// find out if there are update events pending
	/*! \remarks This method returns TRUE if the renderer has not applied
	all pending scene updates yet, or FALSE if there are no updates pending and what 
	is currently rendering or has been rendered is matching what the scene looks like.\n\n
	If the interactive renderer has the concept of an update queue, it can return its
	state here. This function is used by the GetActiveShadeBitmap wait:true MaxScript function
	to be certain that the image being rendered is final and the complete state of
	the rendering. The function waits until IsRendering() AND AnyUpdatesPending() return
	false, and then grabs the image.
	\par Default Implementation:
	<b>{ return FALSE; }</b> */
	virtual BOOL AnyUpdatesPending() { return FALSE; };

    /*! This method is called to abort the render operation. The implementation should stop the rendering process as quickly as possible
    and return only once the render has actually stopped rendering. */
    virtual void AbortRender() = 0;
};

/*! \sa  Class IInteractiveRender,  Class RendProgressCallback,  Class Color\n\n
\brief This class represent a callback object which can be used with an interactive
renderer.
Information set via RendProgressCallback::SetCurField() or
RendProgressCallback::SetSceneStats() will be ignored. If a title is set
via the inherited method SetTitle(), it will appear in the main status
bar, but will be replaced by the 'IRenderTitle' when necessary.  An interactive
renderer should abort if RendProgressCallback::Progress() returns RENDPROG_ABORT. */
class IInteractiveRender::IProgressCallback : public RendProgressCallback
{
public:

	// LO_Horizontal indicates that a single pixel-wide line will grow from left to right,
	// at the top of the rendered region, as the interactive rendering progresses
	// LO_Vertical indicates that the line will grow from top to bottom,
	// at the right of the rendered region.
	enum LineOrientation { LO_Horizontal = 0, LO_Vertical };

	// sets/gets progress line orientation
	/*! \remarks This method allows you to set the orientation of the progress
	line shown during rendering.
	\par Parameters:
	<b>LineOrientation orientation</b>\n\n
	The line orientation which is one of the following; <b>LO_Horizontal</b> or
	<b>LO_Vertical</b>. */
	virtual void SetProgressLineOrientation(LineOrientation orientation) = 0;
	/*! \remarks This method allows you to retrieve the orientation of the
	progress line shown during rendering.
	\return  The line orientation which is one of the following;
	<b>LO_Horizontal</b> or <b>LO_Vertical</b>. */
	virtual LineOrientation GetProgressLineOrientation() const = 0;

	// sets/gets progress line color
	/*! \remarks This method allows you to set the color of the progress line
	shown during rendering.
	\par Parameters:
	<b>const Color\& color</b>\n\n
	The color to set the progress line to. */
	virtual void SetProgressLineColor(const Color& color) = 0;
	/*! \remarks This method returns the color of the progress line shown
	during rendering. */
	virtual const Color& GetProgressLineColor() const = 0;

	// sets/gets the current title. it will appear in the main status bar as "'Title': xx% complete".
	// if no title is provided, 'ActiveShade' will be used instead.
	/*! \remarks This method allows you to set the current title. This will
	appear in the main status bar as "'Title': xx% complete". If no title is
	provided, 'ActiveShade' will be used instead.
	\par Parameters:
	<b>const MCHAR *pProgressTitle</b>\n\n
	The progress title string. */
	virtual void SetIRenderTitle(const MCHAR *pProgressTitle) = 0;
	/*! \remarks This method returns the current title. */
	virtual const MCHAR *GetIRenderTitle() const = 0;
};

//! Class IRenderProgressCallback was renamed and moved to be a member class of IInteractiveRender in 3ds Max 2017; typedef is used for legacy support.
typedef IInteractiveRender::IProgressCallback IRenderProgressCallback;
