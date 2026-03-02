import shutil
import subprocess
import sys
import os

ROOT = os.path.dirname(os.path.abspath(__file__))

def run(dataset_path):
    dataset_path = os.path.abspath(dataset_path)

    if not os.path.exists(dataset_path):
        print("Dataset not found:", dataset_path)
        return

    print("Using dataset:", dataset_path)

    data_dir = os.path.join(ROOT, "data")
    build_dir = os.path.join(ROOT, "build")
    output_dir = os.path.join(ROOT, "outputs")

    os.makedirs(data_dir, exist_ok=True)
    os.makedirs(output_dir, exist_ok=True)

    # overwrite engine input
    shutil.copy(dataset_path, os.path.join(data_dir, "market_data.csv"))

    # run engine
    subprocess.run([os.path.join(build_dir, "orderbook_engine")], check=True)

    # save output
    name = os.path.splitext(os.path.basename(dataset_path))[0]
    shutil.copy(
        os.path.join(build_dir, "alpha_stream.csv"),
        os.path.join(output_dir, f"{name}_alpha.csv")
    )

    print("Output saved to outputs/" + name + "_alpha.csv")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 run_engine.py <dataset.csv>")
    else:
        run(sys.argv[1])
