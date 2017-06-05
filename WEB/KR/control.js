
var counter = 0

var gameModule = (function() {	
	return {
		createButtons: function(amountOfButton) {
				for (var i = 0; i < amountOfButton; i++) {
				var button = document.createElement("Button");
				
				
				button.addEventListener('click', (function (event)  {
					function func(argument) {
						var label =  document.getElementById("number").innerHTML;
						
						if (label == argument.target.innerHTML) {
							counter += 1;
							document.getElementById("result").innerHTML = counter;
						}	
					}
					return func(event)
				}))
				
				button.innerHTML = i + 1;
				document.body.appendChild(button);
			}
		}
	}
}());