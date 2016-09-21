using System;
using System.Collections.Generic;
using System.Web;
using System.Web.Http;
using Autofac;
using Autofac.Extras.CommonServiceLocator;
using Autofac.Integration.Owin;
using log4net.Config;
using Microsoft.Owin;
using Microsoft.Practices.ServiceLocation;
using Owin;
using TrainingIoT.RemoteControl.App.Comm.Mqtt;

[assembly: OwinStartup(typeof(TrainingIoT.RemoteControl.App.Startup))]
namespace TrainingIoT.RemoteControl.App
{
    public partial class Startup
    {
        public void Configuration(IAppBuilder app)
        {
            XmlConfigurator.Configure();

            // Get your HttpConfiguration. In OWIN, you'll create one rather than using GlobalConfiguration.
            var config = new HttpConfiguration();

            // Create Autofac ContainerBuilder
            var builder = new ContainerBuilder();

            RegisterWebApi(builder, config);
            RegisterMvc(builder);
            RegisterServices(builder);

            // Register dependencies, then...
            var container = builder.Build();

            // setup service locator
            var csl = new AutofacServiceLocator(container);
            ServiceLocator.SetLocatorProvider(() => csl);

            // Configure WebApi, MVC and Auth
            ConfigureWebApi(container, config);
            ConfigureMvc(container);
            ConfigureAuth(app);
            ConfigureMapper();

            // OWIN WEB API SETUP:

            // Register the Autofac middleware FIRST, then the Autofac Web API middleware,
            // and finally the standard Web API middleware.
            app.UseAutofacMiddleware(container);
            app.UseAutofacWebApi(config);
            app.UseWebApi(config);
            app.UseAutofacMvc();

            StartBackgroundServices(container);
        }

        private static void StartBackgroundServices(IComponentContext container)
        {
            var services = container.Resolve<IEnumerable<IBackgroundService>>();
            foreach (var backgroundService in services)
            {
                backgroundService.Start();
            }
        }
    }

    public static class OwinContextExtensions
    {
        public static T GetOrCreate<T>(this IOwinContext owinContext, string key, Func<IOwinContext, T> factory)
        {
            var value = owinContext.Get<T>(key);
            if (value == null)
            {
                value = factory(owinContext);
                owinContext.Set(key, value);
            }
            return value;
        }
    }
}
