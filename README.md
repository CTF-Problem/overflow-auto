# 문제 설명
## 요약
- int overflow 를 이용하여 양수끼리의 덧셈을 만족시키기
- 10초 안에 100개의 연산을 맞추면 플레그가 출력됩니다.

## 상세
- 이 환경은 컨테이너 세 개를 생성합니다. nginx, webshell, overflow
- 메인 페이지에 gotty를 통해서 쉘을 열어줍니다. 이 쉘은 netcat을 통해 overflow에 연결됩니다.
- overflow 내부에 C언어로 코딩 된 프로그램이 동작합니다.
- `a + ? = b (a > b)` 인 상황에서 양수인 `?` 를 넣어서 공식을 만족시켜야 합니다.
- 총 100회 반복합니다.
- 일반적으로는 자동화된 도구를 직접 제작해야 가능할 것으로 판단됩니다.
- 터미널의 경우 gotty를 사용중이고 통신 방법은 ws 입니다.
- ws 클라이언트를 구성하고 계산한다음 값을 전송하도록 하여 문제를 해결합니다.


```py
import websocket
import json
import threading
import time
import base64

ws_data = ""

class WebSocketClient:
    def __init__(self, url):
        self.url = url
        self.ws = None
        
    def on_message(self, ws, message):
        try:
            
            decoded_message = base64.b64decode(message[1:]).decode('utf-8')
            print("수신", decoded_message)
            global ws_data
            ws_data += decoded_message
        except Exception as e:
            print(f"일반 메시지: {message}")
            print(f"디코딩 에러: {e}")
    
    def on_error(self, ws, error):
        print(f"에러 발생: {error}")
    
    def on_close(self, ws, close_status_code, close_msg):
        print("웹소켓 연결 종료")
    
    def on_open(self, ws):
        print("웹소켓 연결 성공")
        
    def connect(self):
        websocket.enableTrace(False)  # 디버깅을 위한 로그 활성화
        self.ws = websocket.WebSocketApp(
            self.url,
            on_message=self.on_message,
            on_error=self.on_error,
            on_close=self.on_close,
            on_open=self.on_open
        )
        
    def start(self):
        self.connect()
        # 별도의 스레드에서 웹소켓 실행
        wst = threading.Thread(target=self.ws.run_forever)
        wst.daemon = True
        wst.start()
        
    def send_message(self, message):
        self.ws.send(message)
        print("전송", message)
        
    def close(self):
        if self.ws:
            self.ws.close()

# 사용 예시
if __name__ == "__main__":
    # 웹소켓 서버 URL 설정
    ws_url = "ws://localhost:56468/terminal/ws"
    
    # 클라이언트 생성 및 시작
    client = WebSocketClient(ws_url)
    client.start()
    
    try:
        # 테스트 메시지 전송
        time.sleep(1)  # 연결이 완전히 설정될 때까지 잠시 대기
        client.send_message('{"Arguments": "", "AuthToken": ""}')
        client.send_message('3{"columns":11,"rows":52}')
        while True:
           time.sleep(0.01)
           for i in ws_data.split('\r\n'):
                if ' + ? = ' in i:
                    ws_data = ""
                    arg0, arg1 = i.split(' + ? = ')
                    result = str(2**32 - int(arg0) + int(arg1))
                    print(result)
                    client.send_message(f'1{result}\n')
            
    except KeyboardInterrupt:
        print("프로그램 종료")
        client.close()
```

# 환경 구성
## Signature 및 Flag 설정
docker-compose.yml에 환경변수 설정
- FLAG=bob_dev{flag_example}

## docker compose
```bash
docker compose up -d
```


# 참고자료
- https://youtu.be/acB45XcOp68