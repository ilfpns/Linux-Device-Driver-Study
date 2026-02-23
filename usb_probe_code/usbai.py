import time
import google.generativeai as genai

genai.configure(api_key="")
model = genai.GenerativeModel('gemini-1.5-flash')

DEVICE_PATH = "/dev/mu_usb"

def read_usb_data():
    try:
        with open(DEVICE_PATH, "rb") as f:
            raw_data = f.read(64)
            return raw_data

    except PermissionError:
        print("읽기 권한 없음")
        return None
    except FileNotFoundError:
        print("장치 파일 찾기 실패")
        return None
    except Exception as e:
        print(f"알 수 없는 에러 : {e}")
        return None

def analyze_with_ai(data_bytes):
    hex_string = " ".join([f"{b:02x}" for b in data_bytes])
    prompt = f"""
    내가 만든 리눅스 커널 USB 드라이버에서 방금 16진수 데이터가 들어왔어.
    데이터: [{hex_string}]
    
    이 데이터가 어떤 패턴을 가지는지, 혹은 어떤 의미일 수 있는지 짧고 명확하게 분석해줘.
    """

    print(f"\n[AI에게 질문 전송 중...] 데이터: {hex_string}")
    try:
        response = model.generate_content(prompt)
        return response.text
    except Exception as e:
        return (f"AI API 호출 실패 : {e}")

if __name__ == "__main__":
    print(f"[{DEVICE_PATH}] 장치 모니터링 시작")

    while True:
        data = read_usb_data()

        if data and len(data) > 0:
            ai_answer = analyze_with_ai(data)
            print("=" * 40)
            print("AI 분석 결과:")
            print(ai_answer)
            print("=" * 40)

        time.sleep(2)
