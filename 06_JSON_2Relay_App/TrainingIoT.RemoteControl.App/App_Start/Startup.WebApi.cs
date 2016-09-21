using System.Net.Http.Headers;
using System.Reflection;
using System.Web.Http;
using Autofac;
using Autofac.Integration.WebApi;
using Microsoft.Owin.Security.OAuth;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using TrainingIoT.RemoteControl.Extension.Json.JsonConverters;

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


            config.Formatters.JsonFormatter.UseDataContractJsonSerializer = false;
            // For debugging ease display JSON when browser requests text/plan or html.
            config.Formatters.JsonFormatter.SupportedMediaTypes.Add(MediaTypeHeaderValue.Parse("text/plain"));
            config.Formatters.JsonFormatter.SupportedMediaTypes.Add(MediaTypeHeaderValue.Parse("text/html"));


            SetJsonSerializationSettings(config.Formatters.JsonFormatter.SerializerSettings);

            // Web API routes
            config.MapHttpAttributeRoutes();

            config.Routes.MapHttpRoute(
                name: "DefaultApi",
                routeTemplate: "api/{controller}/{id}",
                defaults: new { id = RouteParameter.Optional }
                );
        }

        public static void SetJsonSerializationSettings(JsonSerializerSettings serializerSettings)
        {
            // handle polymorphic models
            serializerSettings.TypeNameHandling = TypeNameHandling.Auto;
            // serialize enums as string
            serializerSettings.ContractResolver = new CamelCasePropertyNamesContractResolver();
            serializerSettings.Converters.Add(new Newtonsoft.Json.Converters.StringEnumConverter { CamelCaseText = true });
            serializerSettings.Converters.Add(new JsonInheritanceConverter());
        }
    }
}
