using System.Web.Mvc;
using log4net;

namespace TrainingIoT.RemoteControl.App.ErrorLogging
{
    public class LoggingHandleErrorAttribute : HandleErrorAttribute
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof(LoggingHandleErrorAttribute));

        public override void OnException(ExceptionContext filterContext)
        {
            base.OnException(filterContext);

            var ex = filterContext.Exception;
            Log.Error("Error occured", ex);
        }
    }
}