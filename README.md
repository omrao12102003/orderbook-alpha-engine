# Order Book Alpha Signal Engine 🚀

**Professional-grade Order Book Imbalance (OBI) Alpha Engine** inspired by real HFT systems used at firms like Citadel, Jane Street, and Two Sigma.

This project implements **market microstructure → order book → imbalance → alpha signal**, producing BUY / SELL / HOLD decisions from raw order flow data.

> **Not technical analysis. This is raw order flow.**  
> Leading indicator, not lagging candles.

---

## 📌 What This Project Does (Simple Explanation)

Imagine a live marketplace:

- Buyers shout prices they are willing to pay
- Sellers shout prices they are willing to sell
- The **Order Book** tracks all of this in real time

This engine:
1. Rebuilds the order book after **every market event**
2. Measures **buyer vs seller pressure**
3. Computes an **alpha score**
4. Emits a **BUY / SELL / HOLD** signal

---

## 🧠 Core Alpha Logic

### 1️⃣ Order Book Imbalance (OBI)
OBI = (Bid Volume − Ask Volume) / (Bid Volume + Ask Volume)

yaml
Copy code

| OBI Value | Interpretation |
|----------|----------------|
| +1.0 | Only buyers |
| +0.5 | Strong buy pressure |
| 0.0 | Balanced |
| −0.5 | Strong sell pressure |
| −1.0 | Only sellers |

---

### 2️⃣ Depth Imbalance
Depth = Bid Volume / Ask Volume

yaml
Copy code

Shows **strength** of imbalance (2×, 3× buyers = whale activity).

---

### 3️⃣ Spread Penalty
Relative Spread = (Best Ask − Best Bid) / Mid Price

yaml
Copy code

Wide spreads reduce confidence.

---

### 4️⃣ Final Alpha Formula

Alpha = 0.6 × OBI + 0.3 × Depth − 0.1 × Relative Spread

shell
Copy code

### Decision Rule
Alpha > 0.05 → BUY
Alpha < −0.05 → SELL
Otherwise → HOLD

yaml
Copy code

---

## 📊 Example Output

```csv
timestamp,bid_vol,ask_vol,best_bid,best_ask,mid,obi,depth,spread,alpha,decision
1200,800,400,100.0,100.4,100.2,0.33,2.00,0.4,0.79,BUY
2000,1300,400,100.0,100.4,100.2,0.53,3.25,0.4,1.29,BUY
📈 Interpretation

Buyers are 3× deeper than sellers

Whale accumulation detected

Alpha spikes → BUY signal

🧪 Multiple Dataset Support
You can run any CSV dataset without recompiling.

Dataset Folder
Copy code
datasets/
├── test1.csv
├── test2.csv
├── test3.csv
├── test4.csv
Run Engine
bash
Copy code
python3 run_engine.py datasets/test3.csv
Output:

bash
Copy code
outputs/test3_alpha.csv
🏗️ Architecture
sql
Copy code
Phase 1 → Market Event Parsing
Phase 2 → Limit Order Book Maintenance
Phase 3 → Deterministic Replay / Backtest
Phase 4 → Alpha Signal Generation
✔ Deterministic
✔ Single-threaded
✔ No dynamic allocation in hot path
✔ Backtest-first design

📁 Project Structure
makefile
Copy code
OrderBookAlphaEngine/
├── src/            # Core engine
├── include/        # Order book + alpha logic
├── datasets/       # Input CSVs
├── outputs/        # Alpha results
├── ui/             # Web visualization
├── run_engine.py   # Dataset runner
└── README.md
🎓 Why This Project Matters (Interviews)
What most students do

Candlestick patterns

RSI / MACD

Lagging indicators

What this project does

Raw order flow

Market microstructure

Same signals HFT firms pay millions for

💬 Interview one-liner:

“I built a deterministic order book imbalance alpha engine that detects institutional buying pressure before price moves.”

📈 Real-World Relevance
Used in:

Equities

Futures

Crypto

FX

Concepts align directly with:

FRM (Market Risk)

CFA (Alpha generation)

Quant Research / HFT

🚀 Future Upgrades
PnL backtesting

Sharpe ratio

Risk management (VaR)

Live exchange data

Interactive UI

👨‍💻 Author
Omhitendra Kumar Barot
BTech CSE, VIT Vellore (2026)
Aspiring Quantitative Developer

