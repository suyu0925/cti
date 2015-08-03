using System.Web.Mvc;
using System.Web.Http;

namespace Zephyr.Web.Areas.Cti.Controllers
{
    public class CaseController : Controller
    {
        public ActionResult Index()
        {
            ViewBag.Message = "Hello from the DerivedController Index method";
            return View("Index");
        }
    }
}