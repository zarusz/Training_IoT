using System.Net.Http.Headers;
using System.Reflection;
using System.Web.Http;
using Autofac;
using Autofac.Integration.WebApi;
using Microsoft.Owin.Security.OAuth;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using TrainingIoT.RemoteControl.App.Messages.JsonConverters;

namespace TrainingIoT.RemoteControl.App
{
    public partial class Startup
    {
        public static void RegisterWebApi(ContainerBuilder builder, HttpConfiguration config)
        {
            // Register your Web API controllers.
            builder.RegisterApiControllers(Assembly.GetExecutingAssembly());
            // OPTIONAL: Register the Autofac filter provider.
            builder.RegisterWebApiFilterProvider(config);
        }

        public static void ConfigureWebApi(IContainer container, HttpConfiguration config)
        {
            config.DependencyResolver = new AutofacWebApiDependencyResolver(container);

            // Web API configuration and services
            // Configure Web API to use only bearer token authentication.
            config.SuppressDefaultHostAuthentication();
            config.Filters.Add(new HostAuthenticationFilter(OAuthDefaults.AuthenticationType));


            config.Formatters.JsonFormatter.SerializerSettings.ContractResolver = new CamelCasePropertyNamesContractResolver();
            config.Formatters.JsonFormatter.UseDataContractJsonSerializer = false;
            // handle polymorphic models
            config.Formatters.JsonFormatter.SerializerSettings.TypeNameHandling = TypeNameHandling.Auto;
            // serialize enums as string
            config.Formatters.JsonFormatter.SerializerSettings.Converters.Add(
                new Newtonsoft.Json.Converters.StringEnumConverter {CamelCaseText = true});
            // For debugging ease display JSON when browser requests text/plan or html.
            config.Formatters.JsonFormatter.SupportedMediaTypes.Add(MediaTypeHeaderValue.Parse("text/plain"));
            config.Formatters.JsonFormatter.SupportedMediaTypes.Add(MediaTypeHeaderValue.Parse("text/html"));
            config.Formatters.JsonFormatter.SerializerSettings.Converters.Add(new SensorFeatureEventConverter());

            // Web API routes
            config.MapHttpAttributeRoutes();

            config.Routes.MapHttpRoute(
                name: "DefaultApi",
                routeTemplate: "api/{controller}/{id}",
                defaults: new { id = RouteParameter.Optional }
                );
        }
    }
}
