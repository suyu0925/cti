$(function () {
    var ready = false;
    var connect = false;
    var calling = false;
    var case_id;
    var user_id;

    // Log a message
    function log(message) {
        console.log(message);
    }

    var socket = io();
    socket.on('connect', function () {
        log("已连接至服务器");
        connect = true;
        // 连接上服务器后自动切至就绪状态
        switchToReady();
    });

    socket.on('disconnect', function () {
        log("已从服务器断开");
        connect = false;
        switchToNotReady();
    });

    socket.on("oops", function (data) {
        log(data.message);
    });

    socket.on("user_id", function (data) {
        log("分配到的user_id为" + data.user_id);
        user_id = data.user_id;
    });

    socket.on("on-hook", function () {
        log("您已挂机");
        if (calling) {
            // 只有当一通电话结束时，才能提交日志
            setLogButtonEnable(true);
        }
    });

    socket.on("call", function (data) {
        log("您有一个来电：" + JSON.stringify(data, null, 4));
        calling = true;
        switchToNotReady();
        fillData(data);
        case_id = data.case_id;
    });

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

    function fillLog(data) {
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
                var action = "";
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
        var debt = data.debt;
        if (debt) {
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
        } else {
            $('#id').text(data.case_id);
        }
    }

    function clearData() {
        // debt信息
        var i;
        var debtClasses = $('.debtProperties');
        for (i = 0; i < debtClasses.length; i++) {
            $('#' + debtClasses[i].id).text("");
        }

        // 电话信息
        $("#call-table-tbody").empty();
        var titleHTML = "<tr><th width='25%'>电话</th><th width='25%'>类型</th><th width='15%'>关系</th><th width='25%'>姓名</th><th width='10%'>Call</th></tr>";
        var table = $("#call-table");
        table.append(titleHTML);

        for (i = 0; i < 3; i++) {
            var trHTML = "<tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td></tr>";
            table.append(trHTML);
        }

        // 日志
        $('#log-textarea').val("");

        var table = $("#log-table");
        table.empty();
        var titleHTML = "<tr><th width='16%'>备注时间</th><th width='21%'>动作代码</th><th width='49%'>备注</th><th width='14%'>创建人</th></tr>";
        table.append(titleHTML);

        for (var i = 0; i < 3; i++) {
            var trHTML = "<tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td></tr>";
            table.append(trHTML);
        }
    }

    //$('#start-button')[0].onclick = function () {
    //    if (connect) {
    //        log("外呼后台开始拨号");
    //        socket.emit("start");
    //    }
    //};

    function switchToReady() {
        if (!ready) {
            if (!connect) {
                alert("服务器未连接");
            } else {
                ready = true;
                document.getElementById("switchbtn").innerHTML = "<div class='div_switchbtn_1'><span style='float:left; line-height: 24px; text-align:center; width:90px;'>Ready</span><div class='div_box' style='float:left;'></div></div>";

                socket.emit('ready');
            }
        }
    }

    function switchToNotReady() {
        if (ready) {
            ready = false;
            document.getElementById("switchbtn").innerHTML = "<div class='div_switchbtn_0'><div class='div_box' style='float:left;'></div><span style='float:left; line-height: 24px; text-align:center; width:90px;'>Not Ready</span></div>";

            if (connect) {
                socket.emit('not-ready');
            }
        }
    }

    $('#switchbtn').attr("onclick", "").click(function () {
        log("switch btn");
        if (ready) {
            switchToNotReady();
        } else {
            switchToReady();
        }
    });

    $("#log-textarea").focus();

    $('#log-button').attr("onclick", "").click(function () {
        log("click log-button");
        var text = $('#log-textarea').val().trim();
        if (text == '') {
            alert('日志不能为空');
            return;
        }

        log("写入日志: " + text);
        socket.emit('log', {
            case_id: case_id,
            text: text
        });
        case_id = null;

        // 填入当前日志
        var table = $("#log-table");
        // 删除标题
        $("#log-table tr").eq(0).remove();
        var datetime = getDateString(new Date());
        var action = "";
        var trHTML = "<tr><td>" + datetime + "</td><td>" + action + "</td><td>" + text + "</td><td>" + user_id + "</td></tr>";
        table.prepend(trHTML);
        var titleHTML = "<tr><th width='16%'>备注时间</th><th width='21%'>动作代码</th><th width='49%'>备注</th><th width='14%'>创建人</th></tr>";
        table.prepend(titleHTML);

        $('#log-textarea').val("");

        // 切换至就绪状态
        calling = false;
        switchToReady();
        // 清除网页上的客户信息
        // clearData();
        // 不能按提交按钮了
        setLogButtonEnable(false);
    });

    // 初始化时，提交日志按钮就为灰的
    setLogButtonEnable(false);

    function setLogButtonEnable(enable) {
        if (enable) {
            $('#log-button').removeAttr("disabled");
        } else {
            $('#log-button').attr({"disabled": "disabled"});
        }
    }
});
