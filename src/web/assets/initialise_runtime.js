let statusElement = document.getElementById('status');
let Module = {
    // Don't automatically run main() function on page load
    // noInitialRun: true,
    preRun: [],
    postRun: [],
    print: (function () {
        var element = document.getElementById('output');
        if (element) element.value = ''; // clear browser cache
        return function (text) {
            if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
            console.log(text);
            if (element) {
                element.value += text + "\n";
                element.scrollTop = element.scrollHeight; // focus on bottom
            }
        };
    })(),
    printErr: function (text) {
        if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
        console.error(text);
    },
    setStatus: function (text) {
        if (!Module.setStatus.last) Module.setStatus.last = {time: Date.now(), text: ''};
        if (text === Module.setStatus.last.text) return;
        var m = text.match(/([^(]+)\((\d+(\.\d+)?)\/(\d+)\)/);
        var now = Date.now();
        if (m && now - Module.setStatus.last.time < 30) return; // if this is a progress update, skip it if too soon
        Module.setStatus.last.time = now;
        Module.setStatus.last.text = text;
        statusElement.innerHTML = text;
    },
    totalDependencies: 0,
    monitorRunDependencies: function (left) {
        this.totalDependencies = Math.max(this.totalDependencies, left);
        Module.setStatus(left ? 'Preparing... (' + (this.totalDependencies - left) + '/' + this.totalDependencies + ')' : 'All downloads complete.');
    }
};
Module.setStatus('Downloading...');
window.onerror = function(event) {
    // TODO: do not warn on ok events like simulating an infinite loop or exitStatus
    Module.setStatus('Exception thrown, see JavaScript console');
    Module.setStatus = function(text) {
        if (text) Module.printErr('[post-exception status] ' + text);
    };
};

// Define the function to be called when the WebAssembly module is ready to use
Module.onRuntimeInitialized = function()
{
    //  use cwrap() to export the function
    window.bumblevm_input = Module.cwrap(
        'app_input',  // the C function we want to call from JavaScript
        'number',     // its return type (accepted: number, string or array)
        ['string']    // its list of arguments
    );
};

// the BumbleVM action handling function
function bumblevm_action_handler(action_name) {
    document.getElementById('actions').value =  document.getElementById('actions').value + "\n" + action_name
}

// the BumbleVM output handling function
function bumblevm_output_handler(output) {
    document.getElementById('outputs').value =  document.getElementById('outputs').value + "\n" + output
}

// On page load, button events
document.addEventListener("DOMContentLoaded", function()
{
    document.getElementById("btnRun").addEventListener("click", function()
    {
        script = document.getElementById("input").value
        let lines = script.split('\n');
        // Loop through all lines
        for (let j = 0; j < lines.length; j++) {
            window.bumblevm_input(lines[j]);
        }
    });
    document.getElementById("btnClear").addEventListener("click", function()
    {
        document.getElementById("input").value = ''
    });
});