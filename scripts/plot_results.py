import matplotlib.pyplot as plt
import json
import csv
import sys

def plot_gantt_chart(gantt_data, algorithm_name, output_format):
    """
    Generates and saves a Gantt chart from the given Gantt chart data.
    """
    fig, ax = plt.subplots(figsize=(10, 4))
    ax.set_title(f'{algorithm_name} Scheduling - Gantt Chart')
    ax.set_xlabel('Time')
    ax.set_ylabel('Processes')
    ax.set_yticks(range(1, len(set(gantt_data)) + 1))
    ax.set_yticklabels([f'P{i}' for i in sorted(list(set(gantt_data)))])
    ax.set_ylim(0, len(set(gantt_data)) + 1)
    ax.grid(axis='x')

    start_time = 0
    for process_id in gantt_data:
        duration = 1  # Assuming each unit in Gantt chart is 1 time unit
        ax.barh(process_id, duration, left=start_time, height=0.8)
        start_time += duration

    plt.tight_layout()
    plt.savefig(f'{algorithm_name}_gantt_chart.{output_format}')
    plt.close(fig)

def plot_metrics_comparison(metrics_data, output_format):
    """
    Generates and saves bar graphs comparing FCFS and Round Robin metrics.
    """
    metrics = ['CPU Utilization', 'Avg Waiting Time', 'Throughput', 'Starvation Reduction']
    fcfs_values = [metrics_data['FCFS'][metric] for metric in metrics]
    rr_values = [metrics_data['RoundRobin'][metric] for metric in metrics]

    x = range(len(metrics))
    width = 0.35

    fig, ax = plt.subplots(figsize=(12, 6))
    rects1 = ax.bar(x, fcfs_values, width, label='FCFS')
    rects2 = ax.bar([i + width for i in x], rr_values, width, label='Round Robin')

    ax.set_ylabel('Value')
    ax.set_title('Comparison of Scheduling Algorithm Metrics')
    ax.set_xticks([i + width / 2 for i in x])
    ax.set_xticklabels(metrics)
    ax.legend()

    # Attach value labels
    def autolabel(rects):
        for rect in rects:
            height = rect.get_height()
            ax.annotate(f'{height:.2f}',
                        xy=(rect.get_x() + rect.get_width() / 2, height),
                        xytext=(0, 3),  # 3 points vertical offset
                        textcoords="offset points",
                        ha='center', va='bottom')

    autolabel(rects1)
    autolabel(rects2)

    fig.tight_layout()
    plt.savefig(f'metrics_comparison_chart.{output_format}')
    plt.close(fig)


def analyze_starvation_reduction(metrics_data):
    """
    Prints an analysis of starvation reduction achieved by Round Robin.
    """
    starvation_reduction = metrics_data['Starvation Reduction']['FCFS'] # Starvation reduction is calc against FCFS
    print("\nAnalysis of Starvation Reduction:")
    print(f"Round Robin scheduling reduces starvation by approximately {starvation_reduction:.2f}% compared to FCFS in this simulation.")
    if starvation_reduction > 30:
        print("This simulation demonstrates a significant reduction in starvation, exceeding the 30% target.")
    else:
        print("The starvation reduction is below the 30% target. Consider adjusting process parameters or simulation duration.")


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python plot_results.py <input_file_path> <output_format>")
        sys.exit(1)

    input_file_path = sys.argv[1]
    output_format = sys.argv[2] # e.g., 'png', 'pdf', 'svg'

    if output_format not in ['png', 'pdf', 'svg']:
        print("Error: Output format must be 'png', 'pdf', or 'svg'.")
        sys.exit(1)


    if input_file_path.endswith('.json'):
        with open(input_file_path, 'r') as f:
            data = json.load(f)
            gantt_chart_fcfs = data['ganttCharts']['FCFS']
            gantt_chart_rr = data['ganttCharts']['RR']
            metrics = data['metrics']

    elif input_file_path.endswith('.csv'):
        metrics = {'FCFS': {}, 'RoundRobin': {}}
        gantt_chart_fcfs = []
        gantt_chart_rr = []

        with open(input_file_path, 'r') as csvfile:
            csv_reader = csv.reader(csvfile)
            header = next(csv_reader) # skip header
            for row in csv_reader:
                metric_name = row[0]
                if metric_name == 'CPU Utilization':
                    metrics['FCFS']['CPU Utilization'] = float(row[1])
                    metrics['RoundRobin']['CPU Utilization'] = float(row[2])
                elif metric_name == 'Avg Waiting Time':
                    metrics['FCFS']['Avg Waiting Time'] = float(row[1])
                    metrics['RoundRobin']['Avg Waiting Time'] = float(row[2])
                elif metric_name == 'Throughput':
                    metrics['FCFS']['Throughput'] = float(row[1])
                    metrics['RoundRobin']['Throughput'] = float(row[2])
                elif metric_name == 'Starvation Reduction':
                    metrics['FCFS']['Starvation Reduction'] = float(row[1]) # RR vs FCFS
                    metrics['RoundRobin']['Starvation Reduction'] = 0.0 # Not applicable for RR

            # Gantt charts from CSV (assuming process IDs are comma-separated in CSV)
            for row in csv_reader:
                if row and row[0] == 'Gantt Chart (FCFS):':
                    gantt_chart_fcfs = [int(pid.replace('P', '')) for pid in row[1:] if pid]
                elif row and row[0] == 'Gantt Chart (RR):':
                    gantt_chart_rr =  [int(pid.replace('P', '')) for pid in row[1:] if pid]


    else:
        print("Error: Input file format not supported. Use .json or .csv.")
        sys.exit(1)


    plot_gantt_chart(gantt_chart_fcfs, 'FCFS', output_format)
    plot_gantt_chart(gantt_chart_rr, 'RoundRobin', output_format)
    plot_metrics_comparison(metrics, output_format)
    analyze_starvation_reduction(metrics['FCFS'])

    print(f"Gantt charts and metrics comparison chart saved as PNG/PDF/SVG files.")
