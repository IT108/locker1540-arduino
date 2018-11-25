chrome.runtime.onMessage.addListener(
    function(data) {
        var event = new CustomEvent(data.action, {detail: data.data});
        document.dispatchEvent(event);
    }
);