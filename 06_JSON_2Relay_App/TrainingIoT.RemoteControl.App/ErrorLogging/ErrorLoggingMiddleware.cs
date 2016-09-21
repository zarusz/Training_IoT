using System;
using System.Threading.Tasks;
using log4net;
using Microsoft.Owin;

namespace TrainingIoT.RemoteControl.App.ErrorLogging
{
    public class ErrorLoggingMiddleware : OwinMiddleware
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof (ErrorLoggingMiddleware));

        public ErrorLoggingMiddleware(OwinMiddleware next) : base(next)
        {
        }

        #region Overrides of OwinMiddleware

        public override async Task Invoke(IOwinContext context)
        {
            try
            {
                await Next.Invoke(context);
            }
            catch (Exception ex)
            {
                Log.Error("Error occured.", ex);
            }
        }

        #endregion
    }
}