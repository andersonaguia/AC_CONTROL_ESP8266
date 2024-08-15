const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>IOT LAB</title>
    <link
      rel="icon"
      href="https://softexlabs.com.br/static/images/SOFTLABS.svg"
      type="image/x-icon"
    />
    <link rel="preconnect" href="https://fonts.googleapis.com" />
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin />
    <link
      href="https://fonts.googleapis.com/css2?family=DM+Sans:wght@400;500;700&family=PT+Sans:ital,wght@0,400;0,700;1,400;1,700&family=Roboto:wght@300;400;700&display=swap"
      rel="stylesheet"
    />
    <style>
      * {
        margin: 0;
        padding: 0;
        box-sizing: border-box;
      }
      body {
        font-family: "PT Sans", sans-serif;
        font-weight: 400;
        background-color: #f9fafd;
      }
      header {
        width: 100%;
        display: flex;
        justify-content: center;
        align-items: center;
      }
      main {
        width: 100%;
        min-height: 75vh;
        display: flex;
        flex-direction: column;
        justify-content: center;
        align-items: center;
        gap: 1rem;
      }
      section {
        width: 20%;
        height: 60vh;
        background-color: #ffffff;
        padding: 1rem 0.5rem;
        border-radius: 15px;
        display: flex;
        flex-direction: column;
        align-items: center;
        gap: 1rem;
        box-shadow: 6px 6px 18px rgba(0, 0, 0, 0.8), -4px -4px 4px #ffffff;
        transition: all linear 0.3s;
      }
      img {
        width: 10rem;
        height: auto;
      }
      #ice {
        width: 2rem;
      }
      h1 {
        font-size: 2.5rem;
      }

      button {
        color: #ffffff;
        font-size: 1rem;
        cursor: pointer;
        border: none;
      }
      button:hover {
        opacity: 0.8;
      }

      .temperature-display {
        width: 90%;
        display: flex;
        flex-direction: column;
        justify-content: center;
        align-items: center;
        gap: 1rem;
        padding: 1rem;
        border-radius: 10px;
        background-color: #ffffff;
      }
      #temp-value {
        margin-top: 1rem;
        display: flex;
        width: 10rem;
        height: 5rem;
        flex-direction: row;
        align-items: center;
        justify-content: center;
        gap: 0.5rem;
        border-radius: 5px;
      }
      h2 {
        font-size: 2.5rem;
      }
      footer {
        width: 100%;
        display: flex;
        flex-direction: column;
        justify-content: center;
        align-items: center;
        gap: 1rem;
      }
      .footer-img {
        width: 10rem;
        padding: 0 2rem;
      }
      span {
        font-size: 0.8rem;
      }
      #temp-meter {
        width: 1.2rem;
      }
      #powerbtn {
        width: 10rem;
        height: 20rem;
        padding: 0;
        background-color: transparent;
      }
      .unity {
        font-size: 1.5rem;
      }
      .on {
        background-image: url("https://cdn-icons-png.flaticon.com/128/5720/5720464.png");
        background-size: contain;
        background-repeat: no-repeat;
        background-position: center;
      }
      .off {
        background-image: url(https://cdn-icons-png.flaticon.com/128/5720/5720465.png);
        background-size: contain;
        background-repeat: no-repeat;
        background-position: center;
      }
      #place {
        font-size: 1.5rem;
      }
      #header {
        width: 100%;
        display: flex;
        flex-direction: row;
        align-items: center;
        justify-content: space-between;
      }
      #temp-buttons {
        padding: 1rem;
        display: flex;
        width: 10rem;
        height: 5rem;
        flex-direction: row;
        justify-content: space-between;
        gap: 1rem;
        border-radius: 1px;
        align-items: center;
      }
      #up-temp {
        width: 1.5rem;
        height: 1.5rem;
        background-image: url("https://cdn-icons-png.flaticon.com/128/32/32563.png");
        background-size: contain;
        background-repeat: no-repeat;
        background-position: center;
        border-radius: 5px;
      }
      #down-temp {
        width: 1.5rem;
        height: 1.5rem;
        background-image: url("https://cdn-icons-png.flaticon.com/128/153/153604.png");
        background-size: contain;
        background-repeat: no-repeat;
        background-position: center;
        border-radius: 5px;
      }

      #room {
        display: flex;
        flex-direction: column;
      }
      @media (max-width: 768px) {
        header {
          flex-direction: column;
          justify-content: center;
          align-items: center;
        }
        h1 {
          font-size: 1rem;
          margin-top: 1rem;
        }
        .footer-img {
          width: 6rem;
        }
        span {
          font-size: 0.3rem;
        }
        .temp {
          width: 1rem;
          height: 1rem;
        }
        section {
          width: 70%;
        }
        .temperature-display {
          width: 60%;
        }
        .temp-title {
          font-size: 1rem;
        }
        #header {
          justify-content: space-between;
        }
        #powerbtn {
          width: 7rem;
          height: 6rem;
        }
      }
    </style>
    <script>
      let temperature = 24;
      let configuredTemperature = 24;
      function powerOn() {
        setTemperature(temperature);
      }
      function powerOff() {
        fetch("/off").then((response) => {
          if (response.ok) {
            console.log("Enviado comando para desligar o ar");
          } else {
            console.log("Comando falhou, tente novamente!");
          }
        });
      }
      function setTemperature(t) {
        fetch(`/temperature?temp=${t}`).then((response) => {
          if (response.ok) {
            configuredTemperature = t;
            document.getElementById("currentTemperature").textContent = t;
          } else {
            console.log("Comando falhou, tente novamente!");
          }
        });
      }
      function upTemperature() {
        temperature++;
        temperature < 31 ? setTemperature(temperature) : temperature--;
      }
      function downTemperature() {
        temperature--;
        temperature > 16 ? setTemperature(temperature) : temperature++;
      }
      function checkStatus() {
        fetch("/status").then((response) => {
          if (response.ok) {
            response.json().then((data) => {
              console.log("Status:", data);
              let button = document.getElementById("powerbtn");
              let statusMessage = document.getElementById("status-message");
              if (data.status === true) {
                //DESLIGAR
                button.onclick = powerOff; // Altera a função para desligar
                button.classList.remove("off");
                button.classList.add("on");
                statusMessage.textContent = "Ar Ligado";
              } else if (data.status === false) {
                //LIGAR
                button.onclick = powerOn; // Altera a função para ligar
                button.classList.remove("on");
                button.classList.add("off");
                statusMessage.textContent = "Ar Desligado";
              }
            });
          } else {
            console.log("Falha ao obter o status, tente novamente!");
          }
        });
      }

      setInterval(checkStatus, 3000);
    </script>
  </head>
  <body>
    <header>
      <img
        src="https://softexlabs.com.br/static/images/SOFTLABS.svg"
        alt="Logo SOFTEX Labs"
      />
      <h1>IOT LAB</h1>
    </header>
    <main>
      <section class="control">
        <div class="temperature-display">
          <div id="header">
            <div id="room">
              <h2 id="place">Sala 1</h2>
              <spam id="status-message">Ligado</spam>
            </div>
            <img
              id="ice"
              src="https://cdn-icons-png.flaticon.com/128/2530/2530064.png"
              alt="Imagem temperatura"
            />
          </div>
          <div id="temp-value">
            <h2 id="currentTemperature">24</h2>
            <span class="unity">°C</span>
          </div>
        </div>
        <button id="powerbtn" class="off" onclick="powerOn()"></button>
        <div id="temp-buttons">
          <button id="down-temp" onclick="downTemperature()"></button>
          <img
            id="temp-meter"
            src="https://cdn-icons-png.flaticon.com/128/3815/3815282.png"
            alt="Imagem temperatura"
          />
          <button id="up-temp" onclick="upTemperature()"></button>
        </div>
      </section>
    </main>
    <footer>
      <div>
        <img
          class="footer-img"
          src="https://softexlabs.com.br/static/images/softexPE.svg"
          alt="Logo SOFTEX"
        />
      </div>
      <span>&copy; 2024 IOT LAB. Todos os direitos reservados.</span>
    </footer>
  </body>
</html>
)rawliteral";
