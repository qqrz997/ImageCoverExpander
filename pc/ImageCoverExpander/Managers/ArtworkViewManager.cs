using System;
using HMUI;
using SiraUtil.Logging;
using UnityEngine;
using Zenject;

namespace ImageCoverExpander.Managers
{
    // ReSharper disable once ClassNeverInstantiated.Global
    public class ArtworkViewManager : IInitializable, IDisposable
    {
        private const float _expandedSkew = 0f;

        private static readonly Vector3 s_expandedSizeDelta = new Vector2(70.5f, 58f);
        private static readonly Vector3 s_expandedPosition = new Vector3(-34.4f, -56f, 0f);
        
        private readonly SiraLog _siraLog;
        private readonly StandardLevelDetailViewController _standardLevelDetailViewController;
        private readonly MainMenuViewController _mainMenuViewController;
        
        [Inject]
        public ArtworkViewManager(SiraLog siraLog,
                                  StandardLevelDetailViewController standardLevelDetailViewController,
                                  MainMenuViewController mainMenuViewController)
        {
            _siraLog = siraLog;
            _standardLevelDetailViewController = standardLevelDetailViewController;
            _mainMenuViewController = mainMenuViewController;
        }
        
        public void Initialize()
        {
            _mainMenuViewController.didFinishEvent += OnDidFinishEvent;
        }

        public void Dispose()
        {
            _mainMenuViewController.didFinishEvent -= OnDidFinishEvent;
        }

        private void OnDidFinishEvent(MainMenuViewController _, MainMenuViewController.MenuButton __)
        {
            Transform levelBar = _standardLevelDetailViewController.transform
                .Find("LevelDetail")
                .Find("LevelBarBig");

            if (!levelBar) return;

            _siraLog.Info("Changing artwork for " + levelBar.name);

            var image = levelBar.Find("SongArtwork").GetComponent<RectTransform>();
            image.sizeDelta = s_expandedSizeDelta;
            image.localPosition = s_expandedPosition;
            image.SetAsFirstSibling();

            var imageView = image.GetComponent<ImageView>();
            imageView.color = new Color(0.5f, 0.5f, 0.5f, 1f);
            imageView.preserveAspect = false;
            imageView._skew = _expandedSkew;
        }
    }
}
