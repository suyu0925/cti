$(function () {
    data = JSON.parse(data.replace(/&quot;/g, "\""));

    console.log(JSON.stringify(data, null, 4));

    fillData(data);

    function getFixTime(time) {
        if (time < 10) {
            return "0" + time.toString();
        } else {
            return time.toString();
        }
    }

    function getDateString(date) {
        var str = "";
        var year = date.getFullYear();
        var month = getFixTime(date.getMonth() + 1);
        var day = getFixTime(date.getDate());
        var hours = getFixTime(date.getHours());
        var min = getFixTime(date.getMinutes());
        str = year + "-" + month + "-" + day + " " + hours + ":" + min;
        return str;
    }

    function fillDataLabel(id, debt) {
        var properties = id.split('-');

        var d = debt;
        for (var i = 0; i < properties.length; i++) {
            d = d[properties[i]];
        }

        $('#' + id).text(d);
    }

    function fillPhoneNumber(phone_number, type, relationship, name, flag, info) {
        if (phone_number && phone_number.toString().trim().length > 0) {
            var focus = (phone_number == info.phone_number);
            var trHTML = "<tr>";
            if (focus) {
                trHTML += "<td style='color:red;font-weight:bold'>" + phone_number + "</td>";
            } else {
                trHTML += "<td>" + phone_number + "</td>";
            }
            trHTML += "<td>"
                + type + "</td><td>"
                + relationship + "</td><td>"
                + name + "</td><td>"
                + flag + "</td></tr>";
            $("#call-table").append(trHTML);

            // update info
            if (focus) {
                info.focus = info.count;
            }
            info.count++;
        }
    }

    function fillLog(data) {
        var data = {
            debt: data
        };
        var table = $("#log-table");
        table.empty();

        if (!data.debt.logs) {
            for (var i = 0; i < 3; i++) {
                var trHTML = "<tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td></tr>";
                table.append(trHTML);
            }
        } else {
            for (var i = 0; i < data.debt.logs.length; i++) {
                var datetime = getDateString(new Date(parseInt(data.debt.logs[i].datetime)));
                var action = data.debt.logs[i].action;
                var text = data.debt.logs[i].text;
                var user_id = data.debt.logs[i].user_id;
                var trHTML = "<tr><td>" + datetime + "</td><td>" + action + "</td><td>" + text + "</td><td>" + user_id + "</td></tr>";
                table.prepend(trHTML);
            }
        }

        var titleHTML = "<tr><th width='16%'>备注时间</th><th width='21%'>动作代码</th><th width='49%'>备注</th><th width='14%'>创建人</th></tr>";
        table.prepend(titleHTML);
    }

    function fillData(data) {
        var debt = data;
        // 把debt信息都填上去
        var i;
        var debtClasses = $('.debtProperties');
        for (i = 0; i < debtClasses.length; i++) {
            fillDataLabel(debtClasses[i].id, debt);
        }

        // 电话信息
        $("#call-table-tbody").empty();
        var titleHTML = "<tr><th width='25%'>电话</th><th width='25%'>类型</th><th width='15%'>关系</th><th width='25%'>姓名</th><th width='10%'>Call</th></tr>";
        $("#call-table").append(titleHTML);

        var info = {
            count: 0,
            phone_number: data.phone_number,
            focus: -1
        };
        fillPhoneNumber(debt.borrower.phone.mobile, "手机", "本人", debt.borrower.name.personal, "", info);
        fillPhoneNumber(debt.borrower.phone.home, "家庭", "本人", debt.borrower.name.personal, "", info);
        fillPhoneNumber(debt.borrower.phone.office, "公司", "本人", debt.borrower.name.personal, "", info);
        fillPhoneNumber(debt.contacts.spouse.phone.mobile, "手机", "配偶", debt.contacts.spouse.name.personal, "", info);
        fillPhoneNumber(debt.contacts.spouse.phone.home, "家庭", "配偶", debt.contacts.spouse.name.personal, "", info);
        fillPhoneNumber(debt.contacts.guarantor.phone.mobile, "手机", "担保人", debt.contacts.guarantor.name, "", info);
        fillPhoneNumber(debt.contacts.guarantor.phone.home, "家庭", "担保人", debt.contacts.guarantor.name, "", info);
        for (i = 0; i < debt.contacts.other.length; i++) {
            fillPhoneNumber(debt.contacts.other[i].phone, "手机", debt.contacts.other[i].relationship, debt.contacts.other[i].name, "", info);
        }

        // TODO 如果电话信息很多需要滚动到focus的那条
        // var obj = document.getElementById("cc");
        // obj.scrollTop=obj.scrollHeight*(Math.random());

        // 填入日志信息
        fillLog(data);

        parent.iFrameAutoHeight2("iframe_content");//调整父窗口高度
    }
});

function log_form_check() {
    var text = $('#log-textarea').val().trim();
    if (text == '') {
        alert('日志不能为空');
        return false;
    } else {
        return true;
    }
}