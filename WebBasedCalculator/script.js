(function () {
  const expressionEl = document.getElementById('expression');
  const resultEl = document.getElementById('result');

  let currentValue = '0';
  let previousValue = '';
  let operation = null;
  let waitingForOperand = false;
  let powerMode = false;
  let powerBase = null;

  function updateDisplay() {
    resultEl.textContent = currentValue;
    let expr = previousValue;
    if (operation) {
      const opSymbol = { '+': '+', '-': '−', '*': '×', '/': '÷', '^': '^' }[operation] || operation;
      expr += ' ' + opSymbol;
    }
    if (powerMode && powerBase !== null) expr += ' ' + powerBase + '^';
    expressionEl.textContent = expr || '';
  }

  function inputDigit(num) {
    if (waitingForOperand) {
      currentValue = num === '.' ? '0.' : num;
      waitingForOperand = false;
    } else {
      if (num === '.' && currentValue.includes('.')) return;
      if (num === '0' && currentValue === '0' && num !== '.') return;
      if (num !== '.' && currentValue === '0' && !currentValue.includes('.')) {
        currentValue = num;
      } else {
        currentValue += num;
      }
    }
    updateDisplay();
  }

  function factorial(n) {
    n = Math.floor(Number(n));
    if (n < 0 || n > 170) return NaN; // 170! 约等于 JS 安全整数上限
    if (n === 0 || n === 1) return 1;
    let r = 1;
    for (let i = 2; i <= n; i++) r *= i;
    return r;
  }

  function doOperation(op) {
    const prev = parseFloat(previousValue);
    const curr = parseFloat(currentValue);
    let value = NaN;

    switch (op) {
      case '+': value = prev + curr; break;
      case '-': value = prev - curr; break;
      case '*': value = prev * curr; break;
      case '/': value = curr === 0 ? NaN : prev / curr; break;
      case '^': value = Math.pow(prev, curr); break;
      default: break;
    }

    if (Number.isNaN(value)) return '错误';
    if (!Number.isFinite(value)) return '溢出';
    return String(value);
  }

  function handleOperator(op) {
    if (powerMode && powerBase !== null && op === '=') {
      const exp = parseFloat(currentValue);
      const base = parseFloat(powerBase);
      let value = Math.pow(base, exp);
      if (!Number.isFinite(value)) value = '溢出';
      else value = String(value);
      currentValue = value;
      expressionEl.textContent = powerBase + '^' + exp + ' =';
      powerMode = false;
      powerBase = null;
      waitingForOperand = true;
      updateDisplay();
      return;
    }

    if (previousValue !== '' && operation !== null && !waitingForOperand) {
      const result = doOperation(operation);
      currentValue = result;
      previousValue = '';
      operation = null;
    }

    if (op === '=') {
      waitingForOperand = true;
      updateDisplay();
      return;
    }

    previousValue = currentValue;
    operation = op;
    waitingForOperand = true;
    updateDisplay();
  }

  function handleAdvanced(action) {
    const x = parseFloat(currentValue);

    switch (action) {
      case 'factorial':
        if (x < 0 || !Number.isInteger(x)) {
          currentValue = '错误';
        } else {
          const f = factorial(x);
          currentValue = Number.isNaN(f) ? '溢出' : String(f);
          expressionEl.textContent = x + '! =';
        }
        break;
      case 'power':
        powerBase = currentValue;
        powerMode = true;
        currentValue = '0';
        waitingForOperand = true;
        expressionEl.textContent = powerBase + '^';
        break;
      case 'sqrt':
        if (x < 0) {
          currentValue = '错误';
        } else {
          currentValue = String(Math.sqrt(x));
          expressionEl.textContent = '√' + x + ' =';
        }
        break;
      case 'square':
        currentValue = String(x * x);
        expressionEl.textContent = x + '² =';
        break;
      case 'reciprocal':
        if (x === 0) {
          currentValue = '错误';
        } else {
          currentValue = String(1 / x);
          expressionEl.textContent = '1/' + x + ' =';
        }
        break;
      default:
        break;
    }
    waitingForOperand = true;
    updateDisplay();
  }

  function handleFunction(action) {
    switch (action) {
      case 'clear':
        currentValue = '0';
        previousValue = '';
        operation = null;
        powerMode = false;
        powerBase = null;
        waitingForOperand = false;
        expressionEl.textContent = '';
        break;
      case 'backspace':
        if (waitingForOperand) break;
        currentValue = currentValue.slice(0, -1) || '0';
        break;
      case 'percent':
        currentValue = String(parseFloat(currentValue) / 100);
        waitingForOperand = true;
        expressionEl.textContent = currentValue + ' %';
        break;
      default:
        break;
    }
    updateDisplay();
  }

  document.querySelectorAll('.btn').forEach(btn => {
    btn.addEventListener('click', () => {
      if (btn.dataset.num !== undefined) inputDigit(btn.dataset.num);
      else if (btn.dataset.op) handleOperator(btn.dataset.op);
      else if (btn.dataset.action) {
        if (['factorial', 'power', 'sqrt', 'square', 'reciprocal'].includes(btn.dataset.action)) {
          handleAdvanced(btn.dataset.action);
        } else {
          handleFunction(btn.dataset.action);
        }
      }
    });
  });

  updateDisplay();
})();
