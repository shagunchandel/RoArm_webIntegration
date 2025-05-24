const char* main_page = R"rawliteral(

<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width,initial-scale=1">
  <title>Advanced Robotic Control Panel</title>
  <style>
    :root {
      --primary-color: #FFBFA5;
      --primary-hover: #FF9A7E;
      --secondary-color: #FFE7DB;
      --bg-color: #F9F9F9;
      --text-color: #333;
      --font-family: "Segoe UI", Tahoma, Geneva, Verdana, sans-serif;
      --border-radius: 8px;
      --spacing: 1rem;
      --small-spacing: 0.5rem;
      --transition: 0.2s ease-in-out;
      --dark-btn-color: #444;
      --dark-btn-text: #fff;
      --draggable-bg-light: #fff8f0;
      --draggable-bg-dark: #2a2a2a
    }

    body.dark-mode {
      --primary-color: #424242;
      --primary-hover: #616161;
      --secondary-color: #1e1e1e;
      --bg-color: #121212;
      --text-color: #e0e0e0
    }

    *,
    *::before,
    *::after {
      box-sizing: border-box;
      margin: 0;
      padding: 0
    }

    body {
      font-family: var(--font-family);
      background: var(--bg-color);
      color: var(--text-color);
      line-height: 1.5;
      display: flex;
      flex-direction: column;
      min-height: 100vh;
      transition: background 0.3s, color 0.3s
    }

    button,
    input {
      font-family: inherit
    }

    a,
    button {
      cursor: pointer
    }

    .header {
      display: flex;
      justify-content: space-evenly;
      align-items: center;
      background: var(--secondary-color);
      padding: var(--spacing);
      box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
      gap: var(--spacing);
      flex-wrap: wrap
    }

    .info-card {
      background: var(--bg-color);
      padding: var(--small-spacing) var(--spacing);
      border-radius: var(--border-radius);
      box-shadow: 0 1px 2px rgba(0, 0, 0, 0.1);
      display: flex;
      align-items: center;
      gap: var(--small-spacing);
      min-width: 120px;
      justify-content: center
    }

    .info-card span:first-child {
      font-weight: bold;
      margin-right: 0.3rem
    }

    .info-block strong {
      font-size: 0.95rem
    }

    .wifi-tower {
      display: flex;
      align-items: flex-end;
      gap: 2px;
      width: 24px;
      height: 24px;
      justify-content: center
    }

    .wifi-bar {
      width: 3px;
      background: var(--primary-color);
      transition: background var(--transition)
    }

    .bar1 {
      height: 30%
    }

    .bar2 {
      height: 50%
    }

    .bar3 {
      height: 70%
    }

    .bar4 {
      height: 90%
    }

    .main-content {
      flex: 1;
      display: grid;
      grid-template-columns: 320px 1fr 260px;
      gap: var(--spacing);
      padding: var(--spacing)
    }

    .left-sidebar,
    .right-sidebar,
    .control-panel {
      background: var(--bg-color);
      border-radius: var(--border-radius);
      padding: var(--spacing);
      box-shadow: 0 2px 4px rgba(0, 0, 0, 0.08);
      display: flex;
      flex-direction: column;
      gap: var(--spacing)
    }

    .left-sidebar {
      overflow-x: hidden
    }

    .speed-controls {
      display: flex;
      flex-direction: column;
      gap: var(--small-spacing)
    }

    .speed-title {
      font-weight: bold;
      margin-bottom: var(--small-spacing)
    }

    .speed-controls label {
      display: flex;
      align-items: center;
      gap: 0.5rem;
      font-size: 0.95rem;
      cursor: pointer
    }

    .speed-controls input[type="radio"] {
      accent-color: var(--primary-color)
    }

    .sidebar-buttons {
      display: flex;
      flex-direction: column;
      gap: var(--small-spacing)
    }

    .sidebar-buttons button.active {
      background: var(--primary-hover) !important;
      color: #fff !important
    }

    .control-panel {
      display: flex;
      flex-direction: column;
      height: 100%;
      position: relative;
      padding-bottom: 4rem
    }

    .section-title {
      font-size: 1.2rem;
      font-weight: 600;
      border-bottom: 2px solid var(--primary-color);
      padding-bottom: var(--small-spacing)
    }

    .robot-controls {
      display: flex;
      flex-direction: column;
      gap: var(--spacing);
      flex-grow: 1
    }

    .control-group {
      background: var(--secondary-color);
      padding: calc(var(--spacing)*1.5);
      border-radius: var(--border-radius);
      text-align: center;
      box-shadow: 0 1px 2px rgba(0, 0, 0, 0.08);
      flex: 1;
      display: flex;
      flex-direction: column;
      justify-content: center
    }

    .control-group h3 {
      margin-bottom: var(--small-spacing);
      font-size: 1.2rem
    }

    .control-buttons {
      display: flex;
      flex-direction: column;
      gap: var(--small-spacing)
    }

    .emergency-actions {
      position: absolute;
      bottom: 0;
      left: 0;
      right: 0;
      display: flex;
      gap: var(--spacing);
      margin: 0;
      padding: 0 var(--spacing)
    }

    .emergency-actions button {
      flex: 1;
      font-size: 1.2rem;
      padding: 1rem
    }

    .draggable-control {
      position: relative;
      width: 100%;
      min-width: 200px;
      height: 50px;
      margin-bottom: var(--small-spacing);
      background: var(--draggable-bg-light);
      border-radius: 20px;
      overflow: hidden;
      padding: 0 15px;
      box-sizing: border-box;
      transition: background-color var(--transition);
      touch-action: none
    }

    body.dark-mode .draggable-control {
      background: var(--draggable-bg-dark)
    }

    .draggable-track {
      position: absolute;
      top: 50%;
      left: 15px;
      right: 15px;
      height: 6px;
      background: var(--primary-color);
      transform: translateY(-50%)
    }

    .draggable-knob {
      position: absolute;
      top: 50%;
      width: 40px;
      height: 40px;
      background: var(--primary-color);
      border-radius: 50%;
      transform: translate(-50%, -50%);
      transition: background var(--transition);
      cursor: pointer
    }

    .draggable-knob:active,
    .draggable-knob:focus {
      background: var(--primary-hover);
      outline: none
    }

    .control-value {
      font-size: 1rem;
      margin-top: var(--small-spacing)
    }

    .btn-primary {
      background: var(--primary-color);
      color: var(--text-color);
      border: none;
      padding: 0.6rem 1.2rem;
      border-radius: 4px;
      transition: background var(--transition)
    }

    .btn-primary:hover,
    .btn-primary:focus {
      background: var(--primary-hover);
      outline: none
    }

    .btn-secondary {
      background: #fff;
      color: var(--text-color);
      border: 1px solid var(--primary-color);
      padding: 0.4rem 0.8rem;
      border-radius: 4px;
      transition: background var(--transition), color var(--transition)
    }

    .btn-secondary:hover,
    .btn-secondary:focus {
      background: var(--primary-color);
      color: #fff;
      outline: none
    }

    .btn-dark {
      background: var(--dark-btn-color);
      color: var(--dark-btn-text);
      border: none;
      padding: 0.6rem 1.2rem;
      border-radius: 4px;
      transition: background var(--transition);
      font-weight: bold
    }

    .btn-dark:hover,
    .btn-dark:focus {
      background: #222;
      outline: none
    }

    .quick-actions {
      display: flex;
      gap: var(--spacing);
      flex-wrap: wrap
    }

    .right-sidebar {
      background: #fff;
      padding: 1rem;
      border-radius: var(--border-radius);
      box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1)
    }

    .record-section {
      margin-bottom: var(--spacing)
    }

    .record-section .btn-group {
      display: flex;
      gap: 0.5rem
    }

    .record-section button {
      width: 100%;
      padding: 1rem;
      font-size: 1.1rem
    }

    .actions-section {
      margin-top: 1rem
    }

    .actions-section input {
      width: 100%;
      padding: 0.5rem;
      border-radius: 6px;
      border: 1px solid #ccc
    }

    .action-item {
      border: 1px solid var(--primary-color);
      border-radius: var(--border-radius);
      padding: var(--small-spacing);
      background: var(--secondary-color);
      display: flex;
      flex-direction: column;
      justify-content: space-between;
      margin-bottom: var(--small-spacing);
      min-width: 220px;
      box-sizing: border-box
    }

    .action-filename {
      font-weight: bold;
      margin-bottom: var(--small-spacing);
      overflow: hidden;
      text-overflow: ellipsis;
      white-space: nowrap
    }

    .action-buttons {
      display: flex;
      gap: 0.3rem;
      flex-shrink: 0;
      justify-content: space-around
    }

    .action-buttons button {
      padding: 0.3rem 0.6rem;
      font-size: 0.85rem;
      cursor: pointer
    }

    button:focus,
    input:focus {
      outline: 2px solid var(--primary-color);
      outline-offset: 2px
    }

    button:active {
      transform: scale(0.98)
    }

    body.dark-mode .btn-secondary {
      background: #333;
      color: #fff;
      border: 1px solid #888
    }

    body.dark-mode .btn-secondary:hover,
    body.dark-mode .btn-secondary:focus {
      background: #555;
      color: #fff;
      border-color: #999
    }

    body.dark-mode .action-item {
      background: #222;
      border-color: #fff
    }

    body.dark-mode .action-item button {
      background: #333;
      color: #fff;
      border: 1px solid #777
    }

    body.dark-mode .action-item button:hover,
    body.dark-mode .action-item button:focus {
      background: #555;
      border-color: #999
    }

    body.dark-mode .right-sidebar {
      background: #000;
      color: #fff
    }

    body.dark-mode .right-sidebar .record-section,
    body.dark-mode .right-sidebar .actions-section {
      border-bottom: 1px solid #fff;
      padding-bottom: var(--small-spacing);
      margin-bottom: var(--small-spacing)
    }

    @media(max-width:600px) {
      .header {
        flex-direction: column;
        gap: var(--small-spacing)
      }

      .main-content {
        display: flex;
        flex-direction: column;
        padding: var(--spacing)
      }

      .left-sidebar,
      .control-panel,
      .right-sidebar {
        width: 100%
      }

      .draggable-control {
        height: 60px
      }

      .draggable-knob {
        width: 45px;
        height: 45px
      }
    }

    @media(min-width:601px) and (max-width:1024px) {
      .main-content {
        grid-template-columns: 1fr 1fr;
        grid-template-areas: "left-sidebar control-panel""right-sidebar control-panel"
      }

      .left-sidebar {
        grid-area: left-sidebar
      }

      .control-panel {
        grid-area: control-panel
      }

      .right-sidebar {
        grid-area: right-sidebar
      }
    }

    @media(min-width:1025px) {
      .main-content {
        grid-template-columns: 320px 1fr 260px
      }
    }
  </style>
</head>

<body>
  <header class="header" role="banner">
    <div class="info-card info-block" aria-label="Remaining Charge"><span>Remaining Charge</span><strong>95%</strong></div>
    <div class="info-card info-block" aria-label="Expected Runtime"><span>Expected Runtime</span><strong>2hr 34min</strong></div>
    <div class="info-card info-block" aria-label="Battery Life Cycle"><span>Life Cycle</span><strong>245/600</strong></div>
    <div class="info-card info-block" aria-label="Battery Health"><span>Health</span><strong>95%</strong></div>
    <div class="wifi-tower" aria-label="WiFi Strength">
      <div class="wifi-bar bar1"></div>
      <div class="wifi-bar bar2"></div>
      <div class="wifi-bar bar3"></div>
      <div class="wifi-bar bar4"></div>
    </div>
  </header>
  <main class="main-content">
    <aside class="left-sidebar" aria-label="Controls Sidebar">
      <div class="speed-controls">
        <div class="speed-title">Speed</div><label><input type="radio" name="speed" value="slow" checked>Slow</label><label><input type="radio" name="speed" value="moderate">Moderate</label><label><input type="radio" name="speed" value="fast">Fast</label>
      </div>
      <div class="sidebar-buttons"><button class="btn-secondary" onclick="flashLightToggle(this)" onmouseup="this.blur()">Flash Light</button><button class="btn-secondary" onclick="voiceCommand()" onmouseup="this.blur()">Voice Command</button><button class="btn-secondary" onclick="openCreativeStrokes()" onmouseup="this.blur()">Creative Strokes</button><button class="btn-secondary" onclick="openBatteryStats()" onmouseup="this.blur()">Battery Stats</button><button class="btn-secondary" onclick="toggleDarkMode(this)" onmouseup="this.blur()">Dark Mode</button><button class="btn-secondary" onclick="openSettings()" onmouseup="this.blur()">Settings</button></div>
    </aside>
    <section class="control-panel" aria-label="Main Control Panel">
      <div>
        <div class="section-title">Main Control Panel</div>
        <div class="robot-controls">



          <div class="control-group" aria-label="sholder Controls">
            <h3>sholder Controls</h3>
            <div class="draggable-control" id="shoulderControl">
              <div class="draggable-track"></div>
              <div class="draggable-knob" id="sholderKnob" tabindex="0"></div>
            </div>
            <div class="control-value">Rotation: <span id="sholderValue">0</span>°</div>
          </div>

          <div class="control-group" aria-label="Elbow Controls">
            <h3>Elbow Controls</h3>
            <div class="draggable-control" id="elbowControl">
              <div class="draggable-track"></div>
              <div class="draggable-knob" id="elbowKnob" tabindex="0"></div>
            </div>
            <div class="control-value">Rotation: <span id="elbowValue">0</span>°</div>
          </div>
        

          <div class="control-group" aria-label="Base Rotation">
            <h3>Base Rotation</h3>
            <div class="draggable-control" id="baseControl">
              <div class="draggable-track"></div>
              <div class="draggable-knob" id="baseKnob" tabindex="0"></div>
            </div>
            <div class="control-value">Rotation: <span id="baseValue">0</span>°</div>
          </div>


          <div class="control-group" aria-label="Wrist Controls">
            <h3>Wrist Rotation</h3>
            <div class="draggable-control" id="wristControl">
              <div class="draggable-track"></div>
              <div class="draggable-knob" id="wristKnob" tabindex="0"></div>
            </div>
            <div class="control-value">Rotation: <span id="wristValue">0</span>°</div>
          </div>


          <div class="control-group" aria-label="Fingers Controls">
            <h3>Fingers Position</h3>
            <div class="draggable-control" id="fingersControl">
              <div class="draggable-track"></div>
              <div class="draggable-knob" id="fingersKnob" tabindex="0"></div>
            </div>
            <div class="control-value">Rotation: <span id="fingersValue">0</span>%</div>
          </div>
        </div>
      </div>
      <div class="emergency-actions" aria-label="Emergency Actions"><button class="btn-dark" onclick="resetPosition()" onmouseup="this.blur()" aria-label="Emergency Reset">Reset Position</button><button class="btn-dark" onclick="forceStop()" onmouseup="this.blur()" aria-label="Emergency Force Stop">Force Stop</button></div>
    </section>
    <aside class="right-sidebar" aria-label="Recorded Actions">
      <div class="record-section" id="recordSection"><button class="btn-primary" onclick="startRecording()" onmouseup="this.blur()" aria-label="Record activity">Record Activity</button></div>
      <div class="actions-section" aria-label="Search Recorded Actions">
        <div class="section-title" style="font-size:1rem;border:none;padding:0;">Search Recorded Actions</div><input type="text" id="searchAction" placeholder="Search Actions..." aria-label="Search recorded actions" onkeyup="searchActions()">
      </div>
      <div class="actions-section" aria-label="Frequently Used Actions">
        <div class="section-title" style="font-size:1rem;border:none;padding:0;">Frequently Used Actions</div>
        <div class="actions-list" id="frequentActionsList"></div>
      </div>
      <div class="actions-section" aria-label="Recently Added Actions">
        <div class="section-title" style="font-size:1rem;border:none;padding:0;">Recently Added Actions</div>
        <div class="actions-list" id="recentActionsList"></div>
      </div>
    </aside>
  </main>
  <script>
      let frequentActions = [{
          name: "Action 1",
          id: 1,
          looping: false,
          playing: false
        }, {
          name: "Action 2",
          id: 2,
          looping: false,
          playing: false
        }, {
          name: "Action 3",
          id: 3,
          looping: false,
          playing: false
        }, {
          name: "Action 4",
          id: 4,
          looping: false,
          playing: false
        }, {
          name: "Action 5",
          id: 5,
          looping: false,
          playing: false
        }, {
          name: "Action 6",
          id: 6,
          looping: false,
          playing: false
        }, {
          name: "Action 7",
          id: 7,
          looping: false,
          playing: false
        }],
        recentActions = [{
          name: "Recent Action A",
          id: 101,
          looping: false,
          playing: false
        }, {
          name: "Recent Action B",
          id: 102,
          looping: false,
          playing: false
        }, {
          name: "Recent Action C",
          id: 103,
          looping: false,
          playing: false
        }, {
          name: "Recent Action D",
          id: 104,
          looping: false,
          playing: false
        }],
        isRecording = false,
        isPausedRecording = false;

      function initAllDraggables() {
        initDraggableControl("baseControl", "baseKnob", "baseValue", 0, 4095, 3000, moveBase);
        initDraggableControl("wristControl", "wristKnob", "wristValue", 700, 2061, 1500, moveWrist);
        initDraggableControl("fingersControl", "fingersKnob", "fingersValue", 1000, 2100, 1500, setFingersGrip);
        initDraggableControl("elbowControl", "elbowKnob", "elbowValue", 900, 3030, 2047, moveElbow);
        initDraggableControl("shoulderControl", "sholderKnob", "sholderValue", 1000, 3000, 2047, moveSholder);
      }
      window.addEventListener("DOMContentLoaded", () => {
        setTimeout(initAllDraggables, 100);
        renderActionList("frequentActionsList", frequentActions);
        renderActionList("recentActionsList", recentActions)
      });
      window.addEventListener("resize", () => {
        setTimeout(initAllDraggables, 100)
      });

      function renderActionList(id, actions) {
        const container = document.getElementById(id);
        container.innerHTML = "";
        actions.slice(0, 3).forEach(a => {
          const div = document.createElement("div");
          div.className = "action-item";
          div.innerHTML = `<div class="action-filename">${a.name}</div><div class="action-buttons"><button class="btn-secondary" onclick="togglePlay(this,${a.id})" onmouseup="this.blur()" aria-label="Play/Stop action ${a.name}">${a.playing?"⏹":"▶"}</button><button class="btn-secondary" onclick="toggleLoopPause(this,${a.id})" onmouseup="this.blur()" aria-label="Toggle loop/stop for ${a.name}">${a.looping?"⏹":"🔁"}</button><button class="btn-secondary" onclick="editAction(${a.id})" onmouseup="this.blur()" aria-label="Edit action ${a.name}">✎</button><button class="btn-secondary" onclick="deleteAction(${a.id})" onmouseup="this.blur()" aria-label="Delete action ${a.name}">✖</button></div>`;
          container.appendChild(div)
        })
      }

      function moveBase(v) {
        console.log("Base rotation set to:", v)

        fetch("/action", {
          method: "POST",
          headers: {
            "Content-type": "application/json",
          },
          body: JSON.stringify({
            base: v,
          }),
        })
      }

      function moveElbow(d) {
        console.log("Elbow moving:", d)
        fetch("/action", {
          method: "POST",
          headers: {
            "Content-type": "application/json",
          },
          body: JSON.stringify({
            elbow: d,
          }),
        })
        
      }

      function moveWrist(a) {
        console.log("Wrist angle set to:", a)
        fetch("/action", {
          method: "POST",
          headers: {
            "Content-type": "application/json",
          },
          body: JSON.stringify({
            wrist: a,
          }),
        })
      }

      function moveSholder(f) {
        console.log("Wrist angle set to:", f)
        fetch("/action", {
          method: "POST",
          headers: {
            "Content-type": "application/json",
          },
          body: JSON.stringify({
            sholder: f,
          }),
        })
      }

      function setFingersGrip(g) {
        console.log("Fingers grip set to:", g, "%")
        fetch("/action", {
          method: "POST",
          headers: {
            "Content-type": "application/json",
          },
          body: JSON.stringify({
            gripper: g,
          }),
        })
      }

      function voiceCommand() {
        console.log("Voice Command Triggered")
      }

      function resetPosition() {
        alert("Reset Position initiated.");
        console.log("Reset Position Triggered")
      }

      function forceStop() {
        alert("Force Stop initiated. All processes halted!");
        console.log("Force Stop Triggered")
      }

      function flashLightToggle(el) {
        el.classList.toggle("active");
        const lightctrlValue = el.classList.contains("active") ? 255 : 0;
        fetch("/action", {
          method: "POST",
          headers: {
            "Content-type": "application/json",
          },
          body: JSON.stringify({
            lightctrl: lightctrlValue,
          }),
        });

        console.log("Flash Light toggled");
      }

      function toggleDarkMode(el) {
        el.classList.toggle("active");
        document.body.classList.toggle("dark-mode");
        console.log("Dark Mode toggled")
      }

      function openSettings() {
        console.log("Settings opened")
      }

      function openCreativeStrokes() {
        alert("Navigating to Creative Strokes screen...")
      }

      function openBatteryStats() {
        alert("Battery Stats coming soon!");
        console.log("Battery Stats triggered")
      }

      function startRecording() {
        isRecording = true;
        isPausedRecording = false;
        updateRecordSection();
        alert("Recording started (mock).")
      }

      function pauseRecording() {
        if (isRecording && !isPausedRecording) {
          isPausedRecording = true;
          alert("Recording paused (mock).")
        } else if (isRecording && isPausedRecording) {
          isPausedRecording = false;
          alert("Recording resumed (mock).")
        }
        updateRecordSection()
      }

      function stopRecording() {
        if (isRecording) {
          isRecording = false;
          isPausedRecording = false;
          let filename = "Recording_" + new Date().toISOString();
          alert("Recording stopped. Saved as " + filename);
          recentActions.unshift({
            name: filename,
            id: Date.now(),
            looping: false,
            playing: false
          });
          renderActionList("recentActionsList", recentActions);
          updateRecordSection()
        }
      }

      function updateRecordSection() {
        const r = document.getElementById("recordSection");
        r.innerHTML = isRecording ? `<div class="btn-group"><button class="btn-primary" onclick="pauseRecording()" onmouseup="this.blur()" aria-label="Pause/Resume Recording">${isPausedRecording?"⏯":"⏸"}</button><button class="btn-primary" onclick="stopRecording()" onmouseup="this.blur()" aria-label="Stop Recording">⏹</button></div>` : `<button class="btn-primary" onclick="startRecording()" onmouseup="this.blur()" aria-label="Record activity">Record Activity</button>`
      }

      function togglePlay(el, id) {
        function toggle(arr) {
          let a = arr.find(x => x.id === id);
          if (a) {
            a.playing = !a.playing;
            return a.playing
          }
          return false
        }
        const ns = toggle(frequentActions) || toggle(recentActions);
        el.textContent = ns ? "⏹" : "▶";
        console.log("Play toggled for action:", id, "New state:", ns);
        renderActionList("frequentActionsList", frequentActions);
        renderActionList("recentActionsList", recentActions)
      }

      function editAction(id) {
        let newName = prompt("Enter new filename for the action:");
        if (newName) {
          [frequentActions, recentActions].forEach(arr => {
            let a = arr.find(x => x.id === id);
            if (a) a.name = newName
          });
          renderActionList("frequentActionsList", frequentActions);
          renderActionList("recentActionsList", recentActions);
          console.log("Action renamed:", id, "New name:", newName)
        }
      }

      function toggleLoopPause(el, id) {
        function toggle(arr) {
          let a = arr.find(x => x.id === id);
          if (a) {
            a.looping = !a.looping;
            return a.looping
          }
          return false
        }
        const ns = toggle(frequentActions) || toggle(recentActions);
        el.textContent = ns ? "⏹" : "🔁";
        console.log("Loop/Pause toggled for action:", id, "New state:", ns);
        renderActionList("frequentActionsList", frequentActions);
        renderActionList("recentActionsList", recentActions)
      }

      function deleteAction(id) {
        if (confirm("Are you sure you want to delete this action? This cannot be undone.")) {
          frequentActions = frequentActions.filter(x => x.id !== id);
          recentActions = recentActions.filter(x => x.id !== id);
          renderActionList("frequentActionsList", frequentActions);
          renderActionList("recentActionsList", recentActions);
          console.log("Action deleted:", id)
        } else {
          console.log("Delete cancelled for action:", id)
        }
      }

      function addNewAction(name) {
        let id = Date.now();
        recentActions.unshift({
          name,
          id,
          looping: false,
          playing: false
        });
        renderActionList("recentActionsList", recentActions)
      }

      function searchActions() {
        let q = document.getElementById("searchAction").value.toLowerCase();
        let f = frequentActions.filter(x => x.name.toLowerCase().includes(q)),
          r = recentActions.filter(x => x.name.toLowerCase().includes(q));
        renderActionList("frequentActionsList", f);
        renderActionList("recentActionsList", r)
      }

      function initDraggableControl(cid, kid, vid, min, max, init, onUpdate) {
        const c = document.getElementById(cid),
          k = document.getElementById(kid),
          v = document.getElementById(vid),
          cr = c.getBoundingClientRect(),
          rawWidth = (cr.width - 30) > 0 ? (cr.width - 30) : 200;
        let pct = (init - min) / (max - min),
          kx = pct * rawWidth + 15;
        setPos(k, kx);
        update(kx);
        let dragging = false;
        k.addEventListener("mousedown", start);
        k.addEventListener("touchstart", start, {
          passive: false
        });

        function start(e) {
          e.preventDefault();
          dragging = true;
          document.addEventListener("mousemove", move);
          document.addEventListener("touchmove", move, {
            passive: false
          });
          document.addEventListener("mouseup", end);
          document.addEventListener("touchend", end)
        }

        function move(e) {
          if (!dragging) return;
          let cx = e.touches ? e.touches[0].clientX : e.clientX,
            cl = c.getBoundingClientRect().left,
            x = cx - cl;
          if (x < 15) x = 15;
          if (x > cr.width - 15) x = cr.width - 15;
          setPos(k, x);
          update(x)
        }

        function end() {
          dragging = false;
          document.removeEventListener("mousemove", move);
          document.removeEventListener("touchmove", move);
          document.removeEventListener("mouseup", end);
          document.removeEventListener("touchend", end)
        }

          function setPos(el, x) {
            el.style.left = x + "px"
          }

      function update(x) {
        let adj = x - 15,
          p = adj / rawWidth,
          val = Math.round(min + p * (max - min));
        v.textContent = val;
        typeof onUpdate === "function" && onUpdate(val)
      }
    }

    function moveBaseMovement(d) {
      console.log("Base movement:", d)
    }
  </script>
</body>

</html>


)rawliteral";