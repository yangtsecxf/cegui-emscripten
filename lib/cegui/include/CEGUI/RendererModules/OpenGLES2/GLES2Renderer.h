/***********************************************************************
    created:    Wed, 8th Feb 2012
    author:     Lukas E Meindl (based on code by Paul D Turner)
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2012 Paul D Turner & The CEGUI Development Team
 *
 *   Permission is hereby granted, free of charge, to any person obtaining
 *   a copy of this software and associated documentation files (the
 *   "Software"), to deal in the Software without restriction, including
 *   without limitation the rights to use, copy, modify, merge, publish,
 *   distribute, sublicense, and/or sell copies of the Software, and to
 *   permit persons to whom the Software is furnished to do so, subject to
 *   the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/
#pragma once

#include "RendererBase.h"

namespace CEGUI
{
    class OpenGLES2Shader;
    class OpenGLES2ShaderManager;
    class OpenGL3StateChangeWrapper;

/*!
\brief
    Renderer class to interface with OpenGL
*/
class OPENGL_GUIRENDERER_API OpenGLES2Renderer : public OpenGLRendererBase
{
public:
    /*!
    \brief
        Convenience function that creates the required objects to initialise the
        CEGUI system.

        The created Renderer will use the current OpenGL viewport as it's
        default surface size.

        This will create and initialise the following objects for you:
        - CEGUI::OpenGLES2Renderer
        - CEGUI::DefaultResourceProvider
        - CEGUI::System

    \param abi
        This must be set to CEGUI_VERSION_ABI

    \return
        Reference to the CEGUI::OpenGLES2Renderer object that was created.
    */
    static OpenGLES2Renderer& bootstrapSystem(const int abi = CEGUI_VERSION_ABI);

    /*!
    \brief
        Convenience function that creates the required objects to initialise the
        CEGUI system.

        The created Renderer will use the current OpenGL viewport as it's
        default surface size.

        This will create and initialise the following objects for you:
        - CEGUI::OpenGLES2Renderer
        - CEGUI::DefaultResourceProvider
        - CEGUI::System

    \param display_size
        Size object describing the initial display resolution.

    \param abi
        This must be set to CEGUI_VERSION_ABI

    \return
        Reference to the CEGUI::OpenGLES2Renderer object that was created.
    */
    static OpenGLES2Renderer& bootstrapSystem(const Sizef& display_size,
                                            const int abi = CEGUI_VERSION_ABI);

    /*!
    \brief
        Convenience function to cleanup the CEGUI system and related objects
        that were created by calling the bootstrapSystem function.

        This function will destroy the following objects for you:
        - CEGUI::System
        - CEGUI::DefaultResourceProvider
        - CEGUI::OpenGLES2Renderer

    \note
        If you did not initialise CEGUI by calling the bootstrapSystem function,
        you should \e not call this, but rather delete any objects you created
        manually.
    */
    static void destroySystem();

    /*!
    \brief
        Create an OpenGLES2Renderer object.

    \param tt_type
        Specifies one of the TextureTargetType enumerated values indicating the
        desired TextureTarget type to be used.

    \param abi
        This must be set to CEGUI_VERSION_ABI
    */
    static OpenGLES2Renderer& create(const int abi = CEGUI_VERSION_ABI);

    /*!
    \brief
        Create an OpenGLES2Renderer object.

    \param display_size
        Size object describing the initial display resolution.

    \param tt_type
        Specifies one of the TextureTargetType enumerated values indicating the
        desired TextureTarget type to be used.

    \param abi
        This must be set to CEGUI_VERSION_ABI
    */
    static OpenGLES2Renderer& create(const Sizef& display_size,
                                   const int abi = CEGUI_VERSION_ABI);

    /*!
    \brief
        Destroy an OpenGLES2Renderer object.

    \param renderer
        The OpenGLES2Renderer object to be destroyed.
    */
    static void destroy(OpenGLES2Renderer& renderer);

    /*!
    \brief
        Helper to return the reference to the pointer to the standard shader of
        the Renderer

    \return
        Reference to the pointer to the standard shader of the Renderer
    */
    OpenGLES2Shader*& getShaderStandard();

    /*!
    \brief
        Helper to return the attribute location of the position variable in the
        standard shader

    \return
        Attribute location of the position variable in the standard shader
    */
    GLint getShaderStandardPositionLoc();


    /*!
    \brief
        Helper to return the attribute location of the texture coordinate
        variable in the standard shader

    \return
        Attribute location of the texture coordinate variable in the standard
        shader
    */
    GLint getShaderStandardTexCoordLoc();


    /*!
    \brief
        Helper to return the attribute location of the colour variable in the
        standard shader

    \return
        Attribute location of the colour variable in the standard shader
    */
    GLint getShaderStandardColourLoc();

    /*!
    \brief
        Helper to return the uniform location of the matrix variable in the
        standard shader

    \return
        Uniform location of the matrix variable in the standard shader
    */
    GLint getShaderStandardMatrixUniformLoc();

    /*!
    \brief
        Helper to get the wrapper used to check for redundant OpenGL state
        changes.

    \return
        The active OpenGL state change wrapper object.
    */
    OpenGL3StateChangeWrapper* getOpenGLStateChanger();

    // base class overrides / abstract function implementations
    void beginRendering();
    void endRendering();
    Sizef getAdjustedTextureSize(const Sizef& sz) const;
    bool isS3TCSupported() const;
    void setupRenderingBlendMode(const BlendMode mode,
                                 const bool force = false);

private:
    OpenGLGeometryBufferBase* createGeometryBuffer_impl();
    TextureTarget* createTextureTarget_impl();

    void initialiseRendererIDString();

    /*!
    \brief
        Constructor for OpenGL Renderer objects

    \param tt_type
        Specifies one of the TextureTargetType enumerated values indicating the
        desired TextureTarget type to be used.
    */
    explicit OpenGLES2Renderer();

    /*!
    \brief
        Constructor for OpenGL Renderer objects.

    \param display_size
        Size object describing the initial display resolution.

    \param tt_type
        Specifies one of the TextureTargetType enumerated values indicating the
        desired TextureTarget type to be used.
    */
    OpenGLES2Renderer(const Sizef& display_size);

    void initialiseOpenGLShaders();
    void initialiseGLExtensions();

protected:
    /*!
    \brief
        Destructor for OpenGLES2Renderer objects
    */
    virtual ~OpenGLES2Renderer();

private:
    //! initialise OGLES2TextureTargetFactory that will generate TextureTargets
    void initialiseTextureTargetFactory();

    //! init the extra GL states enabled via enableExtraStateSettings
    void setupExtraStates();

    //! The OpenGL shader we will use usually
    OpenGLES2Shader* d_shaderStandard;
    //! Position variable location inside the shader, for OpenGL
    GLint d_shaderStandardPosLoc;
    //! TexCoord variable location inside the shader, for OpenGL
    GLint d_shaderStandardTexCoordLoc;
    //! Color variable location inside the shader, for OpenGL
    GLint d_shaderStandardColourLoc;
    //! Matrix uniform location inside the shader, for OpenGL
    GLint d_shaderStandardMatrixLoc;
    //! The wrapper we use for OpenGL calls, to detect redundant state changes and prevent them
    OpenGL3StateChangeWrapper* d_openGLStateChanger;
    OpenGLES2ShaderManager* d_shaderManager;
    //! whether S3TC texture compression is supported by the context
    bool d_s3tcSupported;
    //! pointer to a helper that creates TextureTargets supported by the system.
    OGLTextureTargetFactory* d_textureTargetFactory;
};

}
