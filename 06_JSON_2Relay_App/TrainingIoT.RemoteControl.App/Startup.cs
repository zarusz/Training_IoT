﻿using System.Web.Http;
using Autofac;
using Autofac.Extras.CommonServiceLocator;
using log4net.Config;
using Microsoft.Owin;
using Microsoft.Practices.ServiceLocation;
using Owin;

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

            // setup service locator
            var csl = new AutofacServiceLocator(container);
            ServiceLocator.SetLocatorProvider(() => csl);
        }
    }
}
