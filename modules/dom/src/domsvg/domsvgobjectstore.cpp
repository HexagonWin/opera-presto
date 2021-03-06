/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*-
**
** Copyright (C) 1995-2006 Opera Software AS.  All rights reserved.
**
** This file is part of the Opera web browser.  It may not be distributed
** under any circumstances.
**
*/

#include "core/pch.h"

#ifdef SVG_DOM

#include "modules/dom/src/domsvg/domsvgobjectstore.h"
#include "modules/dom/src/domglobaldata.h"
#include "modules/dom/src/domobj.h"
#include "modules/dom/src/domsvg/domsvgenum.h"
#include "modules/svg/svg_dominterfaces.h"

#ifdef DOM_NO_COMPLEX_GLOBALS
# define CONST_SIMPLE_ARRAY(name, type) void DOM_##name##_Init (DOM_GlobalData *global_data) { type *local = global_data->name; int i=0;
# define IFS_ENTRY(item1, item2) local[i].ifs = item1, local[i++].atom = item2
# define CONST_SIMPLE_END(name) ; };
#else
# define CONST_SIMPLE_ARRAY(name, type) const type g_DOM_##name[] = {
# define IFS_ENTRY(item1, item2) { item1, item2 }
# define CONST_SIMPLE_END(name) };
#endif // DOM_NO_COMPLEX_GLOBALS

DOM_SVGObjectStore::~DOM_SVGObjectStore()
{
	OP_DELETEA(m_objects);
}

/*
 * These lists must match DOM_SVGElement::GetName()
 *
 * This list must also be grouped by interface, since the iteration
 * assumes this in the iterations.
 *
 * If entries are added or removed, update the counters in the headerfile.
 *
 */
CONST_SIMPLE_ARRAY(svg_element_entries, DOM_SVGInterfaceEntry)
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_LOCATABLE, OP_ATOM_nearestViewportElement),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_LOCATABLE, OP_ATOM_farthestViewportElement),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_SVG_ELEMENT, OP_ATOM_viewport),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_SVG_ELEMENT, OP_ATOM_x),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_SVG_ELEMENT, OP_ATOM_y),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_SVG_ELEMENT, OP_ATOM_width),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_SVG_ELEMENT, OP_ATOM_height),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_SVG_ELEMENT, OP_ATOM_currentTranslate),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_ANIMATED_POINTS, OP_ATOM_points),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_ANIMATED_POINTS, OP_ATOM_animatedPoints),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_ANIMATED_PATH_DATA, OP_ATOM_pathSegList),
    IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_ANIMATED_PATH_DATA, OP_ATOM_normalizedPathSegList),
    IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_ANIMATED_PATH_DATA, OP_ATOM_animatedPathSegList),
    IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_ANIMATED_PATH_DATA, OP_ATOM_animatedNormalizedPathSegList),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_STYLABLE, OP_ATOM_className),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_RECT_ELEMENT, OP_ATOM_width),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_RECT_ELEMENT, OP_ATOM_height),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_RECT_ELEMENT, OP_ATOM_x),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_RECT_ELEMENT, OP_ATOM_y),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_RECT_ELEMENT, OP_ATOM_rx),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_RECT_ELEMENT, OP_ATOM_ry),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_LINE_ELEMENT, OP_ATOM_x1),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_LINE_ELEMENT, OP_ATOM_x2),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_LINE_ELEMENT, OP_ATOM_y1),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_LINE_ELEMENT, OP_ATOM_y2),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_ELLIPSE_ELEMENT, OP_ATOM_cx),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_ELLIPSE_ELEMENT, OP_ATOM_cy),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_ELLIPSE_ELEMENT, OP_ATOM_rx),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_ELLIPSE_ELEMENT, OP_ATOM_ry),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_CIRCLE_ELEMENT, OP_ATOM_cx),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_CIRCLE_ELEMENT, OP_ATOM_cy),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_CIRCLE_ELEMENT, OP_ATOM_r),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_TEXTCONTENT_ELEMENT, OP_ATOM_textLength),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_TEXTCONTENT_ELEMENT, OP_ATOM_lengthAdjust),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_TEXTPATH_ELEMENT, OP_ATOM_startOffset),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_TEXTPATH_ELEMENT, OP_ATOM_method),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_TEXTPATH_ELEMENT, OP_ATOM_spacing),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_TEXTPOSITIONING_ELEMENT, OP_ATOM_x),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_TEXTPOSITIONING_ELEMENT, OP_ATOM_y),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_TEXTPOSITIONING_ELEMENT, OP_ATOM_dx),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_TEXTPOSITIONING_ELEMENT, OP_ATOM_dy),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_TEXTPOSITIONING_ELEMENT, OP_ATOM_rotate),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_TRANSFORMABLE, OP_ATOM_transform),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_URI_REFERENCE, OP_ATOM_href),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_CLIPPATH_ELEMENT, OP_ATOM_clipPathUnits),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_GRADIENT_ELEMENT, OP_ATOM_gradientUnits),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_GRADIENT_ELEMENT, OP_ATOM_gradientTransform),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_GRADIENT_ELEMENT, OP_ATOM_spreadMethod),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_LINEARGRADIENT_ELEMENT, OP_ATOM_x1),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_LINEARGRADIENT_ELEMENT, OP_ATOM_x2),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_LINEARGRADIENT_ELEMENT, OP_ATOM_y1),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_LINEARGRADIENT_ELEMENT, OP_ATOM_y2),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_MASK_ELEMENT, OP_ATOM_maskUnits),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_MASK_ELEMENT, OP_ATOM_maskContentUnits),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_MASK_ELEMENT, OP_ATOM_width),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_MASK_ELEMENT, OP_ATOM_height),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_MASK_ELEMENT, OP_ATOM_x),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_MASK_ELEMENT, OP_ATOM_y),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_PATH_ELEMENT, OP_ATOM_pathLength),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_PATTERN_ELEMENT, OP_ATOM_patternUnits),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_PATTERN_ELEMENT, OP_ATOM_patternContentUnits),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_PATTERN_ELEMENT, OP_ATOM_patternTransform),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_PATTERN_ELEMENT, OP_ATOM_width),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_PATTERN_ELEMENT, OP_ATOM_height),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_PATTERN_ELEMENT, OP_ATOM_x),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_PATTERN_ELEMENT, OP_ATOM_y),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_RADIALGRADIENT_ELEMENT, OP_ATOM_cx),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_RADIALGRADIENT_ELEMENT, OP_ATOM_cy),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_RADIALGRADIENT_ELEMENT, OP_ATOM_fx),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_RADIALGRADIENT_ELEMENT, OP_ATOM_fy),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_RADIALGRADIENT_ELEMENT, OP_ATOM_r),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_STOP_ELEMENT, OP_ATOM_offset),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FILTER_ELEMENT, OP_ATOM_x),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FILTER_ELEMENT, OP_ATOM_y),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FILTER_ELEMENT, OP_ATOM_width),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FILTER_ELEMENT, OP_ATOM_height),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FILTER_ELEMENT, OP_ATOM_filterUnits),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FILTER_ELEMENT, OP_ATOM_primitiveUnits),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FILTER_ELEMENT, OP_ATOM_filterResX), // ?
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FILTER_ELEMENT, OP_ATOM_filterResY), // ?
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FILTER_PRIMITIVE_STANDARD_ATTRIBUTES, OP_ATOM_x),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FILTER_PRIMITIVE_STANDARD_ATTRIBUTES, OP_ATOM_y),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FILTER_PRIMITIVE_STANDARD_ATTRIBUTES, OP_ATOM_width),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FILTER_PRIMITIVE_STANDARD_ATTRIBUTES, OP_ATOM_height),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FILTER_PRIMITIVE_STANDARD_ATTRIBUTES, OP_ATOM_result),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEFLOOD_ELEMENT, OP_ATOM_in1),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECOMPONENTTRANSFER_ELEMENT, OP_ATOM_in1),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEMERGENODE_ELEMENT, OP_ATOM_in1),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FETILE_ELEMENT, OP_ATOM_in1),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEBLEND_ELEMENT, OP_ATOM_in1),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEBLEND_ELEMENT, OP_ATOM_in2),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEBLEND_ELEMENT, OP_ATOM_mode),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECOLORMATRIX_ELEMENT, OP_ATOM_in1),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECOLORMATRIX_ELEMENT, OP_ATOM_type),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECOLORMATRIX_ELEMENT, OP_ATOM_values),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_COMPONENT_TRANSFER_FUNCTION_ELEMENT, OP_ATOM_type),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_COMPONENT_TRANSFER_FUNCTION_ELEMENT, OP_ATOM_tableValues),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_COMPONENT_TRANSFER_FUNCTION_ELEMENT, OP_ATOM_slope),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_COMPONENT_TRANSFER_FUNCTION_ELEMENT, OP_ATOM_intercept),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_COMPONENT_TRANSFER_FUNCTION_ELEMENT, OP_ATOM_amplitude),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_COMPONENT_TRANSFER_FUNCTION_ELEMENT, OP_ATOM_exponent),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_COMPONENT_TRANSFER_FUNCTION_ELEMENT, OP_ATOM_offset),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECOMPOSITE_ELEMENT, OP_ATOM_in1),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECOMPOSITE_ELEMENT, OP_ATOM_in2),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECOMPOSITE_ELEMENT, OP_ATOM_operator),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECOMPOSITE_ELEMENT, OP_ATOM_k1),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECOMPOSITE_ELEMENT, OP_ATOM_k2),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECOMPOSITE_ELEMENT, OP_ATOM_k3),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECOMPOSITE_ELEMENT, OP_ATOM_k4),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECONVOLVEMATRIX_ELEMENT, OP_ATOM_in1),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECONVOLVEMATRIX_ELEMENT, OP_ATOM_orderX), //?
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECONVOLVEMATRIX_ELEMENT, OP_ATOM_orderY), //?
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECONVOLVEMATRIX_ELEMENT, OP_ATOM_targetX),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECONVOLVEMATRIX_ELEMENT, OP_ATOM_targetY),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECONVOLVEMATRIX_ELEMENT, OP_ATOM_kernelMatrix),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECONVOLVEMATRIX_ELEMENT, OP_ATOM_divisor),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECONVOLVEMATRIX_ELEMENT, OP_ATOM_bias),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECONVOLVEMATRIX_ELEMENT, OP_ATOM_edgeMode),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECONVOLVEMATRIX_ELEMENT, OP_ATOM_kernelUnitLengthX), //?
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECONVOLVEMATRIX_ELEMENT, OP_ATOM_kernelUnitLengthY), //?
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FECONVOLVEMATRIX_ELEMENT, OP_ATOM_preserveAlpha),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEDIFFUSELIGHTING_ELEMENT, OP_ATOM_in1),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEDIFFUSELIGHTING_ELEMENT, OP_ATOM_surfaceScale),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEDIFFUSELIGHTING_ELEMENT, OP_ATOM_diffuseConstant),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEDIFFUSELIGHTING_ELEMENT, OP_ATOM_kernelUnitLengthX), //?
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEDIFFUSELIGHTING_ELEMENT, OP_ATOM_kernelUnitLengthY), //?
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEDISTANTLIGHT_ELEMENT, OP_ATOM_azimuth),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEDISTANTLIGHT_ELEMENT, OP_ATOM_elevation),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEPOINTLIGHT_ELEMENT, OP_ATOM_x),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEPOINTLIGHT_ELEMENT, OP_ATOM_y),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEPOINTLIGHT_ELEMENT, OP_ATOM_z),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FESPOTLIGHT_ELEMENT, OP_ATOM_x),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FESPOTLIGHT_ELEMENT, OP_ATOM_y),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FESPOTLIGHT_ELEMENT, OP_ATOM_z),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FESPOTLIGHT_ELEMENT, OP_ATOM_pointsAtX),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FESPOTLIGHT_ELEMENT, OP_ATOM_pointsAtY),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FESPOTLIGHT_ELEMENT, OP_ATOM_pointsAtZ),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FESPOTLIGHT_ELEMENT, OP_ATOM_specularExponent),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FESPOTLIGHT_ELEMENT, OP_ATOM_limitingConeAngle),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEDISPLACEMENTMAP_ELEMENT, OP_ATOM_in1),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEDISPLACEMENTMAP_ELEMENT, OP_ATOM_in2),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEDISPLACEMENTMAP_ELEMENT, OP_ATOM_scale),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEDISPLACEMENTMAP_ELEMENT, OP_ATOM_xChannelSelector),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEDISPLACEMENTMAP_ELEMENT, OP_ATOM_yChannelSelector),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEGAUSSIANBLUR_ELEMENT, OP_ATOM_in1),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEGAUSSIANBLUR_ELEMENT, OP_ATOM_stdDeviationX), //?
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEGAUSSIANBLUR_ELEMENT, OP_ATOM_stdDeviationY), //?
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEIMAGE_ELEMENT, OP_ATOM_preserveAspectRatio),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEMORPHOLOGY_ELEMENT, OP_ATOM_in1),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEMORPHOLOGY_ELEMENT, OP_ATOM_operator),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEMORPHOLOGY_ELEMENT, OP_ATOM_radiusX), //?
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEMORPHOLOGY_ELEMENT, OP_ATOM_radiusY), //?
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEOFFSET_ELEMENT, OP_ATOM_in1),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEOFFSET_ELEMENT, OP_ATOM_dx),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FEOFFSET_ELEMENT, OP_ATOM_dy),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FESPECULARLIGHTING_ELEMENT, OP_ATOM_in1),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FESPECULARLIGHTING_ELEMENT, OP_ATOM_surfaceScale),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FESPECULARLIGHTING_ELEMENT, OP_ATOM_specularConstant),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FESPECULARLIGHTING_ELEMENT, OP_ATOM_specularExponent),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FETURBULENCE_ELEMENT, OP_ATOM_baseFrequencyX), //?
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FETURBULENCE_ELEMENT, OP_ATOM_baseFrequencyY), //?
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FETURBULENCE_ELEMENT, OP_ATOM_numOctaves),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FETURBULENCE_ELEMENT, OP_ATOM_seed),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FETURBULENCE_ELEMENT, OP_ATOM_stitchTiles),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FETURBULENCE_ELEMENT, OP_ATOM_type),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FIT_TO_VIEW_BOX, OP_ATOM_viewBox),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FIT_TO_VIEW_BOX, OP_ATOM_preserveAspectRatio),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_IMAGE_ELEMENT, OP_ATOM_x),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_IMAGE_ELEMENT, OP_ATOM_y),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_IMAGE_ELEMENT, OP_ATOM_width),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_IMAGE_ELEMENT, OP_ATOM_height),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_IMAGE_ELEMENT, OP_ATOM_preserveAspectRatio),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_USE_ELEMENT, OP_ATOM_x),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_USE_ELEMENT, OP_ATOM_y),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_USE_ELEMENT, OP_ATOM_width),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_USE_ELEMENT, OP_ATOM_height),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_USE_ELEMENT, OP_ATOM_instanceRoot),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_USE_ELEMENT, OP_ATOM_animatedInstanceRoot),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_MARKER_ELEMENT, OP_ATOM_refX),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_MARKER_ELEMENT, OP_ATOM_refY),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_MARKER_ELEMENT, OP_ATOM_markerUnits),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_MARKER_ELEMENT, OP_ATOM_markerWidth),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_MARKER_ELEMENT, OP_ATOM_markerHeight),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_MARKER_ELEMENT, OP_ATOM_orientType),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_MARKER_ELEMENT, OP_ATOM_orientAngle),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_A_ELEMENT, OP_ATOM_target),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FOREIGNOBJECT_ELEMENT, OP_ATOM_x),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FOREIGNOBJECT_ELEMENT, OP_ATOM_y),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FOREIGNOBJECT_ELEMENT, OP_ATOM_width),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_FOREIGNOBJECT_ELEMENT, OP_ATOM_height),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_TESTS, OP_ATOM_requiredFeatures),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_TESTS, OP_ATOM_requiredExtensions),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_TESTS, OP_ATOM_systemLanguage),
	IFS_ENTRY(DOM_SVGElementInterface::SVG_INTERFACE_EXTERNAL_RESOURCES_REQUIRED, OP_ATOM_externalResourcesRequired),
	IFS_ENTRY(0, OP_ATOM_UNASSIGNED) // must be last
CONST_SIMPLE_END(svg_element_entries)

CONST_SIMPLE_ARRAY(svg_object_entries, DOM_SVGInterfaceEntry)
	IFS_ENTRY(SVG_DOM_ITEMTYPE_MATRIX, OP_ATOM_matrix),
	IFS_ENTRY(SVG_DOM_ITEMTYPE_PAINT, OP_ATOM_rgbColor), // This is a property of SVGColor really, but how can the inheritance be computed?
	IFS_ENTRY(SVG_DOM_ITEMTYPE_CSSRGBCOLOR, OP_ATOM_red),
	IFS_ENTRY(SVG_DOM_ITEMTYPE_CSSRGBCOLOR, OP_ATOM_green),
	IFS_ENTRY(SVG_DOM_ITEMTYPE_CSSRGBCOLOR, OP_ATOM_blue),
	IFS_ENTRY(0, OP_ATOM_UNASSIGNED) // must be last
CONST_SIMPLE_END(svg_object_entries)

/* static */ OP_STATUS
DOM_SVGObjectStore::Make(DOM_SVGObjectStore*& store, const DOM_SVGInterfaceEntry* entries, DOM_SVGInterfaceSpec ifs)
{
	DOM_SVGObjectStore* tmpstore = OP_NEW(DOM_SVGObjectStore, ());
	if (!tmpstore)
		return OpStatus::ERR_NO_MEMORY;

	tmpstore->m_ifs = ifs;
	tmpstore->m_entries = entries;

	BOOL raise_oom = FALSE;

	int i = 0; // counts the row in entries
	int j = 0; // counts the relevant object count
	while(TRUE)
	{
		const DOM_SVGInterfaceEntry* entry = &entries[i++];
		if (entry->ifs == 0 && entry->atom == OP_ATOM_UNASSIGNED)
			break;

		if (ifs.HasInterface(entry->ifs))
			j++;
	}

	tmpstore->m_count = j;
	if (j > 0)
	{
		tmpstore->m_objects = OP_NEWA(DOM_Object*, j);

		if (!tmpstore->m_objects)
			raise_oom = TRUE;
		else
		{
			for (int k=0;k<j;k++)
				tmpstore->m_objects[k] = NULL;
		}
	}

	if (raise_oom)
	{
		OP_DELETEA(tmpstore->m_objects);
		OP_DELETE(tmpstore);
		return OpStatus::ERR_NO_MEMORY;
	}

	store = tmpstore;
	return OpStatus::OK;
}

void
DOM_SVGObjectStore::GCTrace(DOM_Runtime *runtime)
{
	int i = 0; // counts the row in entries
	int j = 0; // counts the row in the current interface
	while(TRUE)
	{
		const DOM_SVGInterfaceEntry* entry = &m_entries[i++];
		if (entry->ifs == 0 && entry->atom == OP_ATOM_UNASSIGNED)
			break;

		if (m_ifs.HasInterface(entry->ifs))
		{
			DOM_Object::GCMark(m_objects[j]);
			j++;
		}
	}
}

DOM_Object*
DOM_SVGObjectStore::GetObject(OpAtom atom)
{
	int i = 0; // counts the row in entries
	int j = 0; // counts the row in the current interface
	while(TRUE)
	{
		const DOM_SVGInterfaceEntry* entry = &m_entries[i++];
		if (entry->ifs == 0 && entry->atom == OP_ATOM_UNASSIGNED)
			break;

		if (m_ifs.HasInterface(entry->ifs))
		{
			if (entry->atom == atom)
				return m_objects[j];
			j++;
		}
	}
	return NULL;
}

void
DOM_SVGObjectStore::SetObject(OpAtom atom, DOM_Object* obj)
{
	int i = 0; // counts the row in entries
	int j = 0; // counts the row in the current interface
	while(TRUE)
	{
		const DOM_SVGInterfaceEntry* entry = &m_entries[i++];
		if (entry->ifs == 0 && entry->atom == OP_ATOM_UNASSIGNED)
			break;

		if (m_ifs.HasInterface(entry->ifs))
		{
			if (entry->atom == atom)
			{
				m_objects[j] = obj;
				break;
			}
			else
			{
				j++;
			}
		}
	}
}

#endif // SVG_DOM
