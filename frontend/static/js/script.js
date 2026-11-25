const analyzeButton = document.getElementById("analyzeButton");

analyzeButton.addEventListener("click", analyzeDisk);


async function analyzeDisk() {

    const diskSize = Number(document.getElementById("diskSize").value);

    const headPosition = Number(document.getElementById("headPosition").value);

    const requestInput = document.getElementById("requests").value;

    const requests = requestInput
        .split(",")
        .map(value => value.trim())
        .map(Number);

    // Check input values.
    if (
        !Number.isInteger(diskSize) ||
        !Number.isInteger(headPosition) ||
        diskSize <= 0 ||
        headPosition < 0 ||
        headPosition >= diskSize ||
        requests.length === 0 ||
        requests.some(value => !Number.isInteger(value) || value < 0 || value >= diskSize)
    ) {
        alert("Please enter valid disk details and track requests.");
        return;
    }

    analyzeButton.disabled = true;
    analyzeButton.textContent = "Analyzing...";

    try {

        // Send input to Flask.
        const response = await fetch("/analyze", {

            method: "POST",

            headers: {
                "Content-Type": "application/json"
            },

            body: JSON.stringify({
                diskSize: diskSize,
                headPosition: headPosition,
                requests: requests
            })

        });

        const data = await response.json();

        if (!response.ok) {
            throw new Error(data.error || "Analysis failed.");
        }

        // Display scheduling results.
        displayResults(data.results);
        displayPerformanceChart(data.results);

        // Display adaptive recommendation.
        displayRecommendation(data.analysis);

        // Scroll to results.
        document.getElementById("results").scrollIntoView({
            behavior: "smooth"
        });

    }
    catch (error) {

        alert("Error: " + error.message);

    }
    finally {

        analyzeButton.disabled = false;
        analyzeButton.textContent = "Analyse Workload →";

    }

}


// Display all six algorithm results.
function displayResults(results) {

    const container = document.getElementById("resultsContainer");

    container.innerHTML = "";

    results.forEach(result => {

        const card = document.createElement("div");

        card.className = "result-card";

        card.innerHTML = `
            <h3>${result.algorithm}</h3>

            <p>Service Order</p>
            <strong>${result.serviceOrder.join(" → ")}</strong>

            <p>Total Head Movement</p>
            <div class="movement">
                ${result.totalMovement}
            </div>

            <p>Average Head Movement</p>
            <strong>${result.averageMovement.toFixed(2)}</strong>

            <p>Head Path</p>
            <strong>${result.headPath.join(" → ")}</strong>
        `;

        container.appendChild(card);
    });
    }// Performance comparison chart.

let performanceChart = null;

function displayPerformanceChart(results) {

    const labels = results.map(result => result.algorithm);

    const movements = results.map(result => result.totalMovement);

    const ctx = document.getElementById("performanceChart");

    if (performanceChart !== null) {
        performanceChart.destroy();
    }

    performanceChart = new Chart(ctx, {

        type: "bar",

        data: {
            labels: labels,

            datasets: [{
                label: "Total Head Movement",
                data: movements,

                backgroundColor: [
                    "#B98291",
                    "#D5A6B1",
                    "#77745A",
                    "#B69A68",
                    "#B98291",
                    "#D5A6B1"
                ],

                borderColor: "#F0E5D8",
                borderWidth: 1,
                borderRadius: 6
            }]
        },

        options: {
            responsive: true,

            plugins: {
                legend: {
                    labels: {
                        color: "#F0E5D8"
                    }
                }
            },

            scales: {
                x: {
                    ticks: {
                        color: "#E7D8C8"
                    },
                    grid: {
                        color: "rgba(213,166,177,0.1)"
                    }
                },

                y: {
                    beginAtZero: true,
                    ticks: {
                        color: "#E7D8C8"
                    },
                    grid: {
                        color: "rgba(213,166,177,0.1)"
                    }
                }
            }
        }

    });



}


// Display the adaptive recommendation.
function displayRecommendation(analysis) {

    const container = document.getElementById("recommendation");

    container.innerHTML = `
        <h3>${analysis.recommendedAlgorithm}</h3>

        <p>
            <strong>Workload Type:</strong>
            ${analysis.workloadType}
        </p>

        <p>
            ${analysis.explanation}
        </p>
    `;
// Animate disk head movement.

const playButton = document.getElementById("playAnimation");

playButton.addEventListener("click", playHeadAnimation);


async function playHeadAnimation() {

    const diskSize = Number(document.getElementById("diskSize").value);
    const initialHead = Number(document.getElementById("headPosition").value);

    const requestInput = document.getElementById("requests").value;

    const requests = requestInput
        .split(",")
        .map(value => Number(value.trim()));

    if (
        diskSize <= 0 ||
        initialHead < 0 ||
        initialHead >= diskSize ||
        requests.length === 0 ||
        requests.some(value => !Number.isInteger(value) || value < 0 || value >= diskSize)
    ) {
        alert("Please analyse a valid workload first.");
        return;
    }

    playButton.disabled = true;
    playButton.textContent = "Moving...";

    const marker = document.getElementById("headMarker");
    const currentHead = document.getElementById("currentHead");
    const targetTrack = document.getElementById("targetTrack");

    const selectedAlgorithm = document.getElementById("algorithmSelect").value;

const movementPath = [initialHead];

try {

    const response = await fetch("/analyze", {
        method: "POST",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify({
            diskSize: diskSize,
            headPosition: initialHead,
            requests: requests
        })
    });

    const data = await response.json();

    if (!response.ok) {
        throw new Error(data.error || "Analysis failed.");
    }

    const selectedResult = data.results.find(
        result => result.algorithm === selectedAlgorithm
    );

    movementPath.push(...selectedResult.headPath.slice(1));

} catch (error) {

    alert(error.message);
    playButton.disabled = false;
    playButton.textContent = "Play Head Movement →";
    return;

}

    for (let track of movementPath) {

        const position = (track / (diskSize - 1)) * 100;

        marker.style.left = position + "%";

        currentHead.textContent = track;
        targetTrack.textContent = "Target: " + track;

        await new Promise(resolve => setTimeout(resolve, 700));

    }

    playButton.disabled = false;
    playButton.textContent = "Play Again →";
}
}