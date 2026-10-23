import requests
endpoints = ["index.html", "test.pdf", "image.jpg", "missing.txt"]
base_url = "http://localhost:8080/"

for endpoint in endpoints:
    print(f"--- GET /{endpoint} ---")
    try:
        response = requests.get(base_url + endpoint)
        print(f"Status: {response.status_code}")
        print(f"Type:   {response.headers.get('Content-Type')}\n")
    except requests.exceptions.ConnectionError:
        print("Failed: Server is offline.\n")