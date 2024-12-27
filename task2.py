def round_robin():
    def validate_positive_integer(prompt):
        while True:
            try:
                value = int(input(prompt))
                if value < 0:
                    raise ValueError("Value cannot be negative.")
                return value
            except ValueError as e:
                print(f"Invalid input: {e}")
    
    def get_process_data():
        n = validate_positive_integer("Enter the number of processes: ")
        processes = []
        for i in range(n):
            print(f"\nEnter details for Process {i + 1}:")
            arrival_time = validate_positive_integer("  Arrival Time: ")
            burst_time = validate_positive_integer("  Burst Time: ")
            processes.append({"pid": i + 1, "arrival_time": arrival_time, "burst_time": burst_time})
        return processes
    
    def calculate_times(processes, time_quantum):
        n = len(processes)
        waiting_time = [0] * n
        turnaround_time = [0] * n
        response_time = [-1] * n
        remaining_burst_time = [p["burst_time"] for p in processes]
        
        time = 0
        queue = []
        processed = 0
        
        while processed < n:
            # Add processes that have arrived to the queue
            for i, p in enumerate(processes):
                if p["arrival_time"] <= time and i not in queue and remaining_burst_time[i] > 0:
                    queue.append(i)
            if queue:
                current = queue.pop(0)
                # First response time calculation
                if response_time[current] == -1:
                    response_time[current] = time - processes[current]["arrival_time"]
                # Execute the process
                exec_time = min(time_quantum, remaining_burst_time[current])
                remaining_burst_time[current] -= exec_time
                time += exec_time
                # Add to queue if not completed
                if remaining_burst_time[current] > 0:
                    queue.append(current)
                else:
                    # Process completion
                    turnaround_time[current] = time - processes[current]["arrival_time"]
                    waiting_time[current] = turnaround_time[current] - processes[current]["burst_time"]
                    processed += 1
            else:
                time += 1  # Idle time
        return waiting_time, turnaround_time, response_time
    
    processes = get_process_data()
    time_quantum = validate_positive_integer("\nEnter Time Quantum: ")

    # Sort processes by arrival time for convenience
    processes.sort(key=lambda x: x["arrival_time"])
    waiting_time, turnaround_time, response_time = calculate_times(processes, time_quantum)
    # Display results
    print("\nProcess	Arrival Time	Burst Time	Waiting Time	Turnaround Time	Response Time")
    for i, p in enumerate(processes):
        print(f"P{p['pid']}\t{p['arrival_time']}\t\t{p['burst_time']}\t\t{waiting_time[i]}\t\t{turnaround_time[i]}\t\t{response_time[i]}")

    # Calculate and display averages
    avg_waiting_time = sum(waiting_time) / len(processes)
    avg_turnaround_time = sum(turnaround_time) / len(processes)
    avg_response_time = sum(response_time) / len(processes)

    print(f"\nAverage Waiting Time: {avg_waiting_time:.2f}")
    print(f"Average Turnaround Time: {avg_turnaround_time:.2f}")
    print(f"Average Response Time: {avg_response_time:.2f}")


round_robin()
