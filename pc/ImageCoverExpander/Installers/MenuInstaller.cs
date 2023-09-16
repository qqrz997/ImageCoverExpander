using ImageCoverExpander.Managers;
using Zenject;

namespace ImageCoverExpander.Installers
{
    // ReSharper disable once ClassNeverInstantiated.Global
    public class MenuInstaller : Installer
    {
        public override void InstallBindings()
        {
            Container.BindInterfacesTo<ArtworkViewManager>().AsSingle();
        }
    }
}
