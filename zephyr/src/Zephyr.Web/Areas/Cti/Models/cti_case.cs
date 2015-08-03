using System;
using Zephyr.Core;

namespace Zephyr.Web.Areas.Cti.Models
{
    [Module("Cti")]
    public class mms_sendService : ServiceBase<cti_case>
    {
    }

    public class cti_case : ModelBase
    {

        [PrimaryKey]
        public string CaseId { get; set; }
        public DateTime? CaseDateTime { get; set; }
    }
}
