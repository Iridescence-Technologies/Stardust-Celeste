#include <Graphics/2D/Sprite.hpp>
#include <Rendering/Texture.hpp>

namespace Stardust_Celeste::Graphics::G2D {

Sprite::Sprite(u32 tex, Rendering::Rectangle bnd) {
    texture = tex;
    bounds = bnd;

    update_mesh();
}

Sprite::~Sprite() {
    delete verts;
    delete idxs;
}

auto Sprite::update(double dt) -> void {
    // For base: do nothing.
}

auto Sprite::draw() -> void {
    Rendering::TextureManager::get().bind_texture(texture);
    mesh->draw();
}

auto Sprite::set_position(glm::vec2 position) -> void {
    bounds.position = position;
    update_mesh();
}

auto Sprite::set_size(glm::vec2 size) -> void {
    bounds.extent = size;
    update_mesh();
}

auto Sprite::set_rect(Rendering::Rectangle bnd) -> void {
    bounds = bnd;
    update_mesh();
}

auto Sprite::update_mesh() -> void {
    if (verts == nullptr)
        verts = new Rendering::Vertex[4];

    Rendering::Color white = {0xff, 0xff, 0xff, 0xff};

    verts[0] = Rendering::Vertex{
        0.f, 0.f, white, bounds.position.x, bounds.position.y, 0.f};
    verts[1] = Rendering::Vertex{
        1.f, 0.f, white, bounds.position.x + bounds.extent.x, bounds.position.y,
        0.f};
    verts[2] = Rendering::Vertex{1.f,
                                 1.f,
                                 white,
                                 bounds.position.x + bounds.extent.x,
                                 bounds.position.y + bounds.extent.y,
                                 0.f};
    verts[3] = Rendering::Vertex{
        0.f, 1.f, white, bounds.position.x, bounds.position.y + bounds.extent.y,
        0.f};

    if (idxs == nullptr) {
        idxs = new u16[6];
        idxs[0] = 0;
        idxs[1] = 1;
        idxs[2] = 2;
        idxs[3] = 2;
        idxs[4] = 3;
        idxs[5] = 0;
    }

    if (mesh.get() == nullptr)
        mesh = create_scopeptr<Rendering::Mesh>(verts, 4, idxs, 6);
    else {
        mesh->delete_data();
        mesh->add_data(verts, 4, idxs, 6);
    }
}

} // namespace Stardust_Celeste::Graphics::G2D