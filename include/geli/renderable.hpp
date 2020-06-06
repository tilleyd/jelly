#ifndef _GELI_RENDERABLE_HPP_
#define _GELI_RENDERABLE_HPP_

#include <functional>
#include <memory>
#include <vector>

#include <geli/light.hpp>
#include <geli/math/mat4.hpp>
#include <geli/mesh.hpp>
#include <geli/material.hpp>

namespace geli
{

class Light;

/**
 * A renderable containing a mesh, material, transform and child renderables.
 * This is the building block of a scene.
 */
class Renderable : public std::enable_shared_from_this<Renderable>
{

public:

    /**
     * Creates and returns a renderable that is a child of this renderable.
     */
    std::shared_ptr<Renderable> create_child();

    /**
     * Sets the mesh used by the renderable.
     *
     * \param mesh
     *     Index to a mesh stored in the renderer.
     */
    void set_mesh(int mesh) { _mesh = mesh; }

    /**
     * Returns the mesh index.
     */
    int get_mesh() const { return _mesh; }

    /**
     * Sets the material used by the renderable.
     *
     * \param material
     *     Index to a material stored in the renderer.
     */
    void set_material(int material) { _material = material; }

    /**
     * Returns the material index.
     */
    int get_material() const { return _material; }

    /**
     * Attaches the given light to the node and returns its index.
     */
    unsigned int attach_light(const Light&);

    /**
     * Attaches a default light to the node and returns a reference to it.
     *
     * \param t
     *     The type of the light to attach.
     * \param outIndex
     *     If provided, places the light's index into the pointer.
     */
    Light& attach_light(Light::Type t, unsigned int* outIndex = nullptr);

    /**
     * Returns a reference to the light at the given index.
     */
    Light& get_light(unsigned int i) { return _attachedLights[i]; }

    /**
     * Returns a const reference to the light at the given index.
     */
    const Light& get_light(unsigned int i) const { return _attachedLights[i]; }

    /**
     * Returns a const reference to the attached lights.
     */
    const std::vector<Light>& get_lights() const { return _attachedLights; }

    /**
     * Sets the local transform. This flags the renderable as dirty and will
     * cause the children's world transforms to be recalculated at the next call
     * to update_child_world_transforms().
     */
    void set_local_transform(const Mat4f& t);

    /**
     * Returns the local transform of the renderable.
     */
    Mat4f get_local_transform() const { return _local; }

    /**
     * Returns the world transform of the renderable.
     *
     * \warn The results may be invalid if the local transform of any parent
     * changed after the last update.
     */
    Mat4f get_world_transform() const { return _world; }

    /**
     * Updates the entire subtree's world transforms.
     *
     * The immediate children's transforms are only updated if the current
     * renderable is dirty, thereafter this method is recursively called on all
     * children.
     */
    void update_child_world_transforms();

    /**
     * Depth-first traversal of the scene graph, calling the given function
     * with each renderable.
     */
    void for_each(std::function<void(Renderable&)>);

    /**
     * Depth-first traversal of the scene graph, calling the given function
     * with each const renderable.
     */
    void for_each(std::function<void(const Renderable&)>) const;

    /**
     * Returns a weak pointer to the parent renderable.
     */
    std::weak_ptr<Renderable> get_parent() { return _parent; }

    /**
     * Returns the vector of children.
     */
    const std::vector<std::shared_ptr<Renderable>>& get_children() { return _children; }

private:

    friend class Renderer;

    /**
     * Creates a renderable with no mesh and the identity local transform.
     */
    Renderable();

    int _mesh, _material;

    Mat4f _local, _world;
    bool  _dirty;

    std::weak_ptr<Renderable>                _parent;
    std::vector<std::shared_ptr<Renderable>> _children;

    std::vector<Light> _attachedLights;

};

};

#endif
