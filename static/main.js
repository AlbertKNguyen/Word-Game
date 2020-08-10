function addLetter(letter) {
	var curr = $("#display-word").html();

	if (curr == "") {
		curr = letter;
	}
	else {
		curr = curr + " " + letter;
	}

	$("#display-word").html(curr);
}

function resetInterface() {
	$("#btn1").prop("disabled", false);
	$("#btn2").prop("disabled", false);
	$("#btn3").prop("disabled", false);
	$("#btn4").prop("disabled", false);
	$("#btn5").prop("disabled", false);
	$("#btn6").prop("disabled", false);
	$("#btn7").prop("disabled", false);
	$("#btn8").prop("disabled", false);
	$("#btn9").prop("disabled", false);
	$("#display-word").html("");
}

function getLetters() {
	$.get("/list", {}, function (response) {
		var data = JSON.parse(response);
		var list = [];

		for (var i in data) {
			var letter = String.fromCharCode(parseInt(data[i]));
			list.push(letter);
		}

		$("#btn1").html(list[0]);
		$("#btn1").click(function () {
			addLetter(list[0]);
			$(this).prop("disabled", true);
		});

		$("#btn2").html(list[1]);
		$("#btn2").click(function () {
			addLetter(list[1]);
			$(this).prop("disabled", true);
		});

		$("#btn3").html(list[2]);
		$("#btn3").click(function () {
			addLetter(list[2]);
			$(this).prop("disabled", true);
		});

		$("#btn4").html(list[3]);
		$("#btn4").click(function () {
			addLetter(list[3]);
			$(this).prop("disabled", true);
		});

		$("#btn5").html(list[4]);
		$("#btn5").click(function () {
			addLetter(list[4]);
			$(this).prop("disabled", true);
		});

		$("#btn6").html(list[5]);
		$("#btn6").click(function () {
			addLetter(list[5]);
			$(this).prop("disabled", true);
		});

		$("#btn7").html(list[6]);
		$("#btn7").click(function () {
			addLetter(list[6]);
			$(this).prop("disabled", true);
		});

		$("#btn8").html(list[7]);
		$("#btn8").click(function () {
			addLetter(list[7]);
			$(this).prop("disabled", true);
		});

		$("#btn9").html(list[8]);
		$("#btn9").click(function () {
			addLetter(list[8]);
			$(this).prop("disabled", true);
		});
	});
}

function getHighscore() {
	$.get("/getHighscore", {}, function (response) {
		var result = JSON.parse(response);
		$("#highscore").html(result);
		highscore = result;
	});
}

function setHighscore(score) {
	$.post("/setHighscore", { highscore: score }, function (response) {
		var result = JSON.parse(response);
		if (result["status"] == 200) {
			$("#highscore").html(score);
		}
	});
}

// Declare and initialize game variables
var score = 0;
var correctWords = [];
var solutionChecked = false;
var highscore = 0;

$(document).ready(function () {
	// Initialize game
	$("#score").html(score);
	getHighscore();
	getLetters();

	$("#newGame").click(function () {
		location.reload();
	});

	$("#clearWord").click(function () {
		resetInterface();
	});

	$("#checkWord").click(function () {
		var attempt = $("#display-word").html();
		attempt = attempt.replace(/\s/g, '');

		if (attempt !== '' && !correctWords.includes(attempt)) {

			$.get("/checkWord", { word: attempt }, function (response) {
				var answer = JSON.parse(response);
				var word = answer["word"];
				var valid = answer["valid"];

				resetInterface();

				if (valid) {
					correctWords.push(word);
					var curr = $("#correct").html();
					if (curr == "") {
						curr = word;
					} else {
						curr = curr + ", " + word;
					}
					$("#correct").html(curr);

					if (!solutionChecked) {
						if (word.length != 9) {
							score += Math.floor(Math.pow(word.length, 1.5) * 100);
						} else {
							score += Math.floor(Math.pow(word.length, 1.5) * 100) + 9000;
						}
						$("#score").html(score);

						if (score > highscore) {
							setHighscore(score);
							highscore = score;
						}
					}
				}
				
			});
		} else {
			resetInterface();
		}
	});

	$("#showSolution").click(function () {
		solutionChecked = true;
		$(this).prop("disabled", true);
		$.get("/solution", {}, function (response) {
			var answers = JSON.parse(response);
			var solution = $("#solution").html();

			for (var i in answers) {
				solution = solution + ", " + answers[i];
			}
			solution = solution.slice(2);

			$("#solution").html(solution);
		});
	});
});
