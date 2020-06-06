#include <geli/renderable.hpp>

using namespace geli;

Renderable::Renderable() :
    _mesh(-1),
    _material(-1),
    _local(1.0f),
    _world(1.0f),
    _dirty(false) // not dirty since local is identity transform
{}

std::shared_ptr<Renderable> Renderable::create_child()
{
    std::shared_ptr<Renderable> r = std::shared_ptr<Renderable>(new Renderable());
    _children.push_back(r);
    r->_parent = std::weak_ptr<Renderable>(shared_from_this());
    return r;
}

unsigned int Renderable::attach_light(const Light& l)
{
    _attachedLights.push_back(l);
    return _attachedLights.size() - 1;
}

Light& Renderable::attach_light(Light::Type t, unsigned int* outIndex)
{
    _attachedLights.emplace_back(t);
    unsigned int i = _attachedLights.size() - 1;
    if (outIndex) {
        *outIndex = i;
    }
    return _attachedLights[i];
}

void Renderable::set_local_transform(const Mat4f& t)
{
    _local = t;
    _dirty = true;
}

void Renderable::update_child_world_transforms()
{
    // update attachments
    for (Light& l : _attachedLights) {
        if (_dirty || l._dirty) {
            l._update_world_transform(_world);
        }
    }

    // update children
    for (std::shared_ptr<Renderable> child : _children) {
        if (_dirty || child->_dirty) {
            // recalculate the child's transforms
            child->_world = (_world * child->get_local_transform());
            child->_dirty = true;
        }

        child->update_child_world_transforms();
    }

    _dirty = false;
}

void Renderable::for_each(std::function<void(Renderable&)> f)
{
    f(*this);
    for (std::shared_ptr<Renderable> child : _children) {
        child->for_each(f);
    }
}

void Renderable::for_each(std::function<void(const Renderable&)> f) const
{
    f(*this);
    for (std::shared_ptr<const Renderable> child : _children) {
        child->for_each(f);
    }
}
