function get_server_address() {
	dump("get address\n");
	var cmdline = window.arguments[0].QueryInterface(Components.interfaces.nsICommandLine);
	return cmdline.getArgument(0);
}

function load_page() {
	dump("load_page\n");
	var mbrowser = document.getElementById("main_browser");
	mbrowser.loadURI(get_server_address());
}

function refresh_page() {
	dump("refresh page\n");
	var main_browser = document.getElementById("main_browser");
	main_browser.reload();
}

function reboot_system() {
	dump("reboot system\n");
	var params = {inn:{name:"重新启动", description:"您确定要重新启动客户端?"}, out:null}; 

	window.openDialog("chrome://xenlogin/content/confirm_dialog.xul", "", "chrome, dialog, modal, resizable=no, minimizable=no, close=no, titlebar=no, centerscreen=yes,width=246px,height=112px", params);
	
	if (params.out) {
		var c = Components.classes["@ccoss.com/desktop;1"].createInstance();
		c = c.QueryInterface(Components.interfaces.nsICcoss);
		c.reboot();
		dump("reboot\n");
	}
}

function shutdown_system() {
	dump("shutdown system\n");
	var params = {inn:{name:"关闭", description:"您确定要关闭客户端?"}, out:null}; 

	window.openDialog("chrome://xenlogin/content/confirm_dialog.xul", "", "chrome, dialog, modal, resizable=no, minimizable=no, close=no, titlebar=no, centerscreen=yes,width=246px,height=112px", params);

	if (params.out) {
		dump("shutdown\n");
		var c = Components.classes["@ccoss.com/desktop;1"].createInstance();
        c = c.QueryInterface(Components.interfaces.nsICcoss);
        c.shutdown();
	}
}

