var onMessage = function (data) {
    switch (data.action) {
        case 'scanner': {
            chrome.tabs.query({url: "file:///*"}, function (tab) {
                for (var i = 0; i < tab.length; i++) {
                    chrome.tabs.sendMessage(tab[i].id, data);
                    console.log(data)
                }
            });
        }
    }
};
chrome.runtime.onMessageExternal.addListener(onMessage);
chrome.management.launchApp("efhoealofoamekoeibnbjicccijlmncg", function(){
    if(chrome.runtime.lastError) console.error(chrome.runtime.lastError);
    else console.log("App launched");
});
