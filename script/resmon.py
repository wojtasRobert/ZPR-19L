# Client for the resource monitor daemon
import requests

if __name__ == '__main__':
    response: requests.Response = requests.post('http://127.0.0.1:8081/')
    print(response.text)
