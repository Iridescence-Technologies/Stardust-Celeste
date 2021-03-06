#include <Graphics/2D/Sprite.hpp>
#include <Stardust-Celeste.hpp>
#include <Utilities/Controllers/VitaController.hpp>
#include <Utilities/Input.hpp>

using namespace Stardust_Celeste;
using namespace Stardust_Celeste::Utilities::Input;

class GameState : public Core::ApplicationState {

  public:
    GameState() : vitaCTRL(nullptr) {}

    void on_update(Core::Application *app, double dt) {
        appref = app;
        Utilities::Input::update();
    }
    void on_draw(Core::Application *app, double dt) {
        if (sprite.get() != nullptr)
            sprite->draw();
    }

    static void quit(std::any a) {
        SC_APP_INFO("Pressed Cross!");
        auto gs = std::any_cast<GameState *>(a);
        SC_APP_INFO("SECRET: {}", gs->secret_value);
        gs->appref->exit();
    }

    void on_start() {
        SC_APP_INFO("Hello World!");
        auto vitaCTRL = new Utilities::Input::VitaController();

        vitaCTRL->add_command(
            {static_cast<int>(Utilities::Input::VitaButtons::Cross),
             Utilities::KeyFlag::Press},
            {GameState::quit, this});

        Utilities::Input::add_controller(vitaCTRL);

        Rendering::RenderContext::get().matrix_ortho(-1, 1, -1, 1, -1, 1);
        Rendering::RenderContext::get().set_mode_2D();

        tex_id = Rendering::TextureManager::get().load_texture(
            "./container.jpg", SC_TEX_FILTER_NEAREST, SC_TEX_FILTER_NEAREST,
            true);

        auto tex = Rendering::TextureManager::get().get_texture(tex_id);
        sprite = create_scopeptr<Graphics::G2D::Sprite>(
            tex_id, Rendering::Rectangle{{-1, -1}, {2, 2}});
    }

    void on_cleanup() {}

  private:
    bool added;
    const int secret_value = 12;
    VitaController *vitaCTRL;
    Core::Application *appref;
    ScopePtr<Graphics::G2D::Sprite> sprite;
    u32 tex_id;
};

class GameApplication : public Core::Application {
  public:
    void on_start() override {
        state = create_refptr<GameState>();
        Application::get().push_state(state);
    }

  private:
    RefPtr<GameState> state;
};

Core::Application *CreateNewSCApp() {
    Core::AppConfig config;
    config.headless = false;

    Core::PlatformLayer::get().initialize(config);

    return new GameApplication();
}