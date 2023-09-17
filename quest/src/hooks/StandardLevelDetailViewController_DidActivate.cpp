#include "hooking.hpp"
#include "logging.hpp"

#include "GlobalNamespace/StandardLevelDetailViewController.hpp"
#include "GlobalNamespace/StandardLevelDetailView.hpp"
#include "GlobalNamespace/LevelBar.hpp"
#include "HMUI/ImageView.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/RectTransform.hpp"

#define EXPANDED_SKEW 0.0f
#define EXPANDED_SIZE_DELTA {50.5f, 58.0f}
#define EXPANDED_POSITION {-34.5f, -56.0f, 0.0f}

MAKE_HOOK_MATCH(StandardLevelDetailViewController_DidActivate,
                &GlobalNamespace::StandardLevelDetailViewController::DidActivate, void,
                GlobalNamespace::StandardLevelDetailViewController *self, bool firstActivation, bool _, bool __) {
    StandardLevelDetailViewController_DidActivate(self, firstActivation, _, __);

    GlobalNamespace::LevelBar *levelBar = self->standardLevelDetailView->levelBar;

    INFO("Expanding artwork for {0}", levelBar->get_name());

    HMUI::ImageView *imageView = levelBar->songArtworkImageView;
    imageView->set_color({0.5f, 0.5f, 0.5f, 1.0f});
    imageView->set_preserveAspect(false);
    imageView->skew = EXPANDED_SKEW;

    UnityEngine::RectTransform *image = imageView->get_rectTransform();
    image->set_sizeDelta(EXPANDED_SIZE_DELTA);
    image->set_localPosition(EXPANDED_POSITION);
    image->SetAsFirstSibling();
}

#undef EXPANDED_SKEW
#undef EXPANDED_SIZE_DELTA
#undef EXPANDED_POSITION

void install_StandardLevelDetailViewController_DidActivate_hook(Logger &logger) {
    INSTALL_HOOK(logger, StandardLevelDetailViewController_DidActivate);
}

RegisterInstallFunction(install_StandardLevelDetailViewController_DidActivate_hook);