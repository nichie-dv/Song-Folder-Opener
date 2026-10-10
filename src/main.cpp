#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/CustomSongLayer.hpp>
class $modify(MyCustomSongLayer, CustomSongLayer) {
	bool init(CustomSongDelegate* delegate) {
		if (!CustomSongLayer::init(delegate)) return false;

		auto spr = CircleButtonSprite::createWithSpriteFrameName(
			"gj_folderBtn_001.png",
			1,
			CircleBaseColor::Green,
			CircleBaseSize::Small
		);
		spr->setScale(0.6f);

		auto btn = CCMenuItemSpriteExtra::create(
			spr,
			this,
			menu_selector(MyCustomSongLayer::onOpenSongFolder)
		);
		btn->setID("open-song-folder-button"_spr);
		btn->setPosition({403, -50});

		if (auto menu = this->m_mainLayer->getChildByType<CCMenu*>(0)) { menu->addChild(btn); }

		return true;
	}

	void onOpenSongFolder(CCObject*) {
		auto path = std::string(MusicDownloadManager::sharedState()->pathForSongFolder(1));
		std::error_code ec;

		if (!std::filesystem::exists(path, ec)) {
			if (ec) log::error("couldn't check song folder {}: {}", path, ec.message());
			else  log::error("song folder path missing: {}", path);
			
			return;
		}

		utils::file::openFolder(path);
	}
};

/*
Not sure if this works on ios please fact check me on this and lmk
*/