import pandas as pd
import matplotlib.pyplot as plt

# Load the ApacheBench data
data = pd.read_csv('benchmark.tsv', sep='\t')

# Plot Request Number vs. Response Time (ms)
plt.figure(figsize=(10, 5))
plt.plot(data.index, data['ttime'], color='blue', alpha=0.6)

plt.title('C Threadpool HTTP Server: Latency under Load (10,000 Requests)')
plt.xlabel('Request Number')
plt.ylabel('Total Response Time (ms)')
plt.grid(True)

# Save the graph as an image for GitHub
plt.savefig('performance_graph.png', dpi=300)
print("Graph saved as performance_graph.png")