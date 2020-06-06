#ifndef _GELI_RENDERER_HPP_
#define _GELI_RENDERER_HPP_

#include <memory>
#include <vector>

#include <geli/framebuffer.hpp>
#include <geli/material.hpp>
#include <geli/mesh.hpp>
#include <geli/renderable.hpp>
#include <geli/shader.hpp>

namespace geli
{

class Window;

/**
 * The core 3D renderer that contains all scene elements and performs the
 * real-time rendering stages.
 */
class Renderer
{

public:

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    Renderer(Window*);

    /**
     * Creates the renderable as a direct child of the scene root.
     */
    std::shared_ptr<Renderable> create_renderable();

    /**
     * Adds a mesh to the renderer and returns its index.
     */
    int add_mesh(std::shared_ptr<Mesh>);

    /**
     * Returns the mesh at a given index.
     */
    std::shared_ptr<Mesh> get_mesh(int i);

    /**
     * Sets the mesh at the given index.
     */
    void set_mesh(int i, std::shared_ptr<Mesh>);

    /**
     * Adds a material to the renderer and returns its index.
     */
    int add_material(std::shared_ptr<Material>);

    /**
     * Returns the material at a given index.
     */
    std::shared_ptr<Material> get_material(int i);

    /**
     * Sets the material at the given index.
     */
    void set_material(int i, std::shared_ptr<Material>);

    /**
     * Updates all world transforms and renders the scene.
     */
    void render();

    /**
     * Updates all world transforms and renders only the hierarchy of the
     * given renderable.
     */
    void render(Renderable&);

    /**
     * Uses the given framebuffer as the render target for subsequent rendering.
     *
     * \param buffers
     *     A vector of color buffer indices to use as active targets. Only
     *     used if multiple textures were attached to the buffer as color
     *     attachments. If null, only the first color buffer will be used.
     *
     * \warn Certain framebuffer operations such as creating a new framebuffer
     * or attaching textures will replace the currently bound framebuffer.
     *
     * \throw std::runtime_error if the framebuffer does not have the necessary
     * attachments or if the format of an attachment is incorrect.
     */
    void set_framebuffer(const Framebuffer&, const std::vector<unsigned int>* buffers = nullptr);

    /**
     * Reverts to the default framebuffer (i.e. the window viewport) as the
     * render target for subsequent rendering.
     */
    void reset_framebuffer();

    /**
     * Sets the projection matrix.
     */
    void set_projection_matrix(const Mat4f& m) { _projMatrix = m; };

    /**
     * Sets the view matrix.
     */
    void set_view_matrix(const Mat4f& m) { _viewMatrix = m; };

    /**
     * Sets the camera position.
     */
    void set_camera_position(const Vec3f& v) { _cameraPosition = v; };

    /**
     * Sets the background color.
     */
    void set_background_color(const Vec3f& color);

    /**
     * Sets the ambient light color.
     */
    void set_ambient_light(const Vec3f& color);

    /**
     * Sets the directional light.
     */
    void set_directional_light(const Light& l);

    /**
     * Sets the point light at index i.
     */
    void set_point_light(const Light& l, unsigned int i);

    /**
     * Clears the point light at index i.
     */
    void clear_point_light(unsigned int i);

    /**
     * Sets the spot light at index i.
     */
    void set_spot_light(const Light& l, unsigned int i);

    /**
     * Clears the spot light at index i.
     */
    void clear_spot_light(unsigned int i);

    /**
     * Sets the skybox cube map.
     */
    void set_skybox(std::shared_ptr<geli::Texture> t) { _skyboxCube = t; }

private:

    std::shared_ptr<Renderable> _root;

    std::vector<std::shared_ptr<Mesh>>     _meshes;
    std::vector<std::shared_ptr<Material>> _materials;

    std::shared_ptr<geli::Shader> _geomShader;
    std::shared_ptr<geli::Shader> _skyboxShader;
    std::shared_ptr<geli::Shader> _bloomShader;
    std::shared_ptr<geli::Shader> _postShader;

    std::shared_ptr<geli::Framebuffer> _framebuffer;
    std::shared_ptr<geli::Texture>     _colorBuffer1;
    std::shared_ptr<geli::Texture>     _colorBuffer2;
    std::shared_ptr<geli::Texture>     _colorBuffer3;
    std::shared_ptr<geli::Texture>     _depthBuffer;
    std::shared_ptr<geli::Texture>     _skyboxCube;

    Mat4f _projMatrix;
    Mat4f _viewMatrix;
    Vec3f _cameraPosition;

    unsigned int _prevPointLightCount;
    unsigned int _prevSpotLightCount;

    Window* _window;

};

};

#endif
