let index = 0;
let timer = null;
let total = 0;

// ------------------------
// Fetch total events
// ------------------------
async function fetchCount() {
  const res = await fetch("/count");
  const data = await res.json();
  total = data.count;
}

// ------------------------
// Fetch and render one event
// ------------------------
async function step() {
  if (index >= total) return;

  const res = await fetch(`/event/${index}`);
  const d = await res.json();

  render(d);
  index++;
}

// ------------------------
// Play / Pause / Reset
// ------------------------
function play() {
  if (timer) return;
  timer = setInterval(step, 700);
}

function pause() {
  clearInterval(timer);
  timer = null;
}

function reset() {
  pause();
  index = 0;

  document.getElementById("event").innerText = "";
  document.getElementById("metrics").innerText = "";
  document.getElementById("alpha").innerText = "";
  document.getElementById("decision").innerText = "";
  document.getElementById("explanation").innerText = "";
}

// ------------------------
// Render UI
// ------------------------
function render(d) {

  // ---- Event ----
  document.getElementById("event").innerText =
    `Timestamp (ns): ${d.timestamp_ns}`;

  // ---- Metrics ----
  document.getElementById("metrics").innerText =
    `Bid Volume: ${d.bid_volume}
Ask Volume: ${d.ask_volume}
Best Bid: ${d.best_bid}
Best Ask: ${d.best_ask}
Mid Price: ${d.mid_price}
Spread: ${d.spread}`;

  // ---- Alpha ----
  document.getElementById("alpha").innerText =
    `Order Book Imbalance (OBI): ${d.obi}
Depth Imbalance: ${d.depth_imbalance}
Normalized Spread: ${d.spread_norm}
Alpha: ${d.alpha}`;

  // ---- Decision ----
  const decisionEl = document.getElementById("decision");
  decisionEl.innerText = `Decision: ${d.decision}`;
  decisionEl.className = `decision ${d.decision}`;

  // ---- Explanation ----
  document.getElementById("explanation").innerText =
    explain(d);
}

// ------------------------
// Explanation Logic
// ------------------------
function explain(d) {

  // Incomplete book case
  if (parseFloat(d.mid_price) === 0) {
    return (
      "The order book does not yet contain both valid bid and ask prices. " +
      "Without spread-based confirmation, the system conservatively issues a HOLD signal."
    );
  }

  let text = "";

  if (parseFloat(d.obi) > 0) {
    text += "Bid-side liquidity exceeds ask-side liquidity, indicating buying pressure. ";
  } else {
    text += "Ask-side liquidity exceeds bid-side liquidity, indicating selling pressure. ";
  }

  if (parseFloat(d.spread_norm) < 0.001) {
    text += "The bid-ask spread is narrow, confirming healthy liquidity conditions. ";
  } else {
    text += "The bid-ask spread is relatively wide, reducing confidence in the signal. ";
  }

  text += `The composite alpha value is ${d.alpha}, resulting in a ${d.decision} decision.`;

  return text;
}

// ------------------------
// Init
// ------------------------
fetchCount();
