using System.Reflection;
using System.Web.Mvc;
using System.Web.Optimization;
using System.Web.Routing;
using Autofac;
using Autofac.Integration.Mvc;

namespace TrainingIoT.RemoteControl.App
{
    public partial class Startup
    {
        public static void RegisterMvc(ContainerBuilder builder)
        {
            // Register your MVC controllers.
            builder.RegisterControllers(Assembly.GetExecutingAssembly());
        }

        public static void ConfigureMvc(IContainer container)
        {
            DependencyResolver.SetResolver(new AutofacDependencyResolver(container));

            AreaRegistration.RegisterAllAreas();
            RegisterFilters(GlobalFilters.Filters);
            ConfigureRoutes(RouteTable.Routes);
            RegisterBundles(BundleTable.Bundles);
        }

        private static void ConfigureRoutes(RouteCollection routes)
        {
            routes.IgnoreRoute("{resource}.axd/{*pathInfo}");
            routes.MapRoute(
                name: "Default",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "Home", action = "Index", id = UrlParameter.Optional }
                );

            /*
            routes.MapRoute(
                name: "DeviceDetail",
                url: "Device/{deviceId}",                
                defaults: new { controller = "RemoteControl", action = "Device" }
                );

            routes.MapRoute(
                name: "DeviceList",
                url: "Device",
                defaults: new { controller = "RemoteControl", action = "Index" }
                );
            */
        }


        // For more information on bundling, visit http://go.microsoft.com/fwlink/?LinkId=301862
        private static void RegisterBundles(BundleCollection bundles)
        {
            bundles.Add(new ScriptBundle("~/bundles/jquery").Include(
                        "~/Scripts/jquery-{version}.js"));

            // Use the development version of Modernizr to develop with and learn from. Then, when you're
            // ready for production, use the build tool at http://modernizr.com to pick only the tests you need.
            bundles.Add(new ScriptBundle("~/bundles/modernizr").Include(
                        "~/Scripts/modernizr-*"));

            bundles.Add(new ScriptBundle("~/bundles/bootstrap").Include(
                      "~/Scripts/bootstrap.js",
                      "~/Scripts/respond.js"));

            bundles.Add(new StyleBundle("~/Content/css").Include(
                      "~/Content/bootstrap.css",
                      "~/Content/site.css"));
        }

        private static void RegisterFilters(GlobalFilterCollection filters)
        {
            filters.Add(new HandleErrorAttribute());
        }

    }
}