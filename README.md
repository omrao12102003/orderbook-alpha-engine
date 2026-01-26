# 🚀 Order Book Alpha Signal Engine (Phase 1–4)

This project demonstrates how professional trading systems analyze **order book data** to generate BUY / SELL / HOLD signals.

It is written in **C++17**, designed step-by-step, and explained so **even beginners can understand it**.

---

## What is an Order Book?

An order book contains all active **buy orders** and **sell orders** in the market.

Example:

BIDS (Buyers)        ASKS (Sellers)
100.05 × 50          100.10 × 40
100.00 × 30          100.15 × 60

Price moves when **buying pressure** or **selling pressure** dominates.

---

## What This Project Does

1. Reads market events (orders & trades)
2. Builds a live limit order book
3. Measures buyer vs seller pressure
4. Generates BUY / SELL / HOLD signals

This project **does NOT place real trades**.  
It focuses only on **signal generation** (Phase 1–4).

---

## Project Phases Overview

Market Events  
↓  
Phase 1 — Event Model  
↓  
Phase 2 — Limit Order Book  
↓  
Phase 3 — Deterministic Replay  
↓  
Phase 4 — Alpha Signal Engine  

---

## Phase 1 — Market Event Model

Each market action is represented as an **event**:

- ADD order
- MODIFY order
- CANCEL order
- TRADE execution

Every event contains:
- Timestamp (nanoseconds)
- Order ID
- Side (BUY / SELL)
- Price
- Quantity

This makes the system **deterministic and replayable**.

---

## Phase 2 — Limit Order Book

The order book stores all active buy and sell orders.

Features:
- Separate bid and ask sides
- Price-time priority (FIFO)
- Best bid / best ask queries
- Deterministic updates

This mimics how real exchanges work.

---

## Phase 3 — Deterministic Replay

Market events are replayed **one by one** in time order.

Why this matters:
- No look-ahead bias
- Same input → same output
- Easy debugging

---

## Phase 4 — Alpha Signal Engine

This phase generates trading signals using **market microstructure**.

### Signals Used

Order Book Imbalance (OBI):
OBI = (BidVolume − AskVolume) / (BidVolume + AskVolume)

Depth Imbalance:
Confirms buyer or seller dominance

Spread Penalty:
Large spreads reduce signal confidence

### Composite Alpha Formula

Alpha =
0.6 × OBI  
+ 0.3 × Depth Imbalance  
− 0.1 × Normalized Spread  

### Decision Rules

- Alpha ≥ +0.05 → BUY
- Alpha ≤ −0.05 → SELL
- Otherwise → HOLD

---

## Example Output

TS=100 | Alpha=0.032 | HOLD  
TS=200 | Alpha=0.061 | BUY  
TS=300 | Alpha=-0.071 | SELL  

---

## Project Structure

include/
- Phase1_Event.hpp
- Phase2_OrderBook.hpp
- Phase3_Backtester.hpp
- Phase4_AlphaSignal.hpp

src/
- main.cpp

---

## Build & Run

mkdir build  
cd build  
cmake ..  
make  
./orderbook_engine  

---

## Why This Project is Valuable

- Shows understanding of market microstructure
- Uses professional event-driven design
- Deterministic and reproducible
- Written in clean C++17
- Ideal for quant / trading system interviews

---

## Author

Omhitendra Kumar Barot  
B.Tech CSE, VIT Vellore (2026)  
Interest: Quantitative Finance & Trading Systems
