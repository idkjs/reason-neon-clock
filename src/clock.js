const phrases = [
  'IT IS',
  'ABOUT',
  'NEARLY',
  'TEN',
  'QUARTER',
  'TWENTY',
  'FIVE',
  'HALF',
  'PAST',
  'TO',
  'ONE',
  'TWO',
  'THREE',
  'FOUR',
  'FIVE',
  'SIX',
  'SEVEN',
  'EIGHT',
  'NINE',
  'TEN',
  'ELEVEN',
  'NOON',
  'MIDNIGHT',
  'O\' CLOCK',
  'IN THE',
  'MORNING',
  'AFTERNOON',
  'EVENING',
];

function getNow () {
  const now = new Date(Date.now());
  const hour = now.getHours();
  const minute = now.getMinutes();
  const second = now.getSeconds();
  const display = now.toLocaleString();

  return {
    hour,
    minute,
    second,
    display,
  };
}

function getReadoutConfig ({ hour, minute }) {
  const lastMinuteMark = Math.floor(minute / 5) * 5;
  const distFromLast = minute - lastMinuteMark;
  const isExact = distFromLast === 0;
  const isNearly = !isExact && distFromLast > 2;
  const isAbout = !isExact && !isNearly;
  const nearestMinuteMark = isNearly
    ? (lastMinuteMark + 5) % 60
    : lastMinuteMark;
  const isOClock = nearestMinuteMark === 0;
  const isPast = !isOClock && nearestMinuteMark <= 30;
  const isTo = !isOClock && !isPast;
  const minuteMark = (isPast || isOClock)
    ? nearestMinuteMark
    : 60 - nearestMinuteMark;

  const nearestHour = (isTo || (isOClock && isNearly)) ? (hour + 1) % 24 : hour;
  const nearestHour12 = nearestHour > 12
    ? nearestHour - 12
    : nearestHour;
  const isNoon = nearestHour === 12;
  const isMidnight = nearestHour === 0;
  const isMorning = !isMidnight && nearestHour < 12;
  const isAfternoon = nearestHour > 12 && nearestHour <= 18;
  const isEvening = nearestHour > 18;

  return {
    isExact,
    isAbout,
    isNearly,

    minute: minuteMark,
    isOClock: isOClock && !isNoon && !isMidnight,
    isPast,
    isTo,

    hour: nearestHour12,
    isNoon,
    isMidnight,
    isMorning,
    isAfternoon,
    isEvening,
  };
}

function getHighlights (config) {
  return [
    true, // IT IS
    config.isAbout, // ABOUT
    config.isNearly, // NEARLY
    config.minute === 10, // TEN
    config.minute === 15, // QUARTER
    config.minute === 20 || config.minute === 25, // TWENTY
    config.minute === 5 || config.minute === 25, // FIVE
    config.minute === 30, // HALF
    config.isPast, // PAST
    config.isTo, // TO
    config.hour === 1, // ONE
    config.hour === 2, // TWO
    config.hour === 3, // THREE
    config.hour === 4, // FOUR
    config.hour === 5, // FIVE
    config.hour === 6, // SIX
    config.hour === 7, // SEVEN
    config.hour === 8, // EIGHT
    config.hour === 9, // NINE
    config.hour === 10, // TEN
    config.hour === 11, // ELEVEN
    config.isNoon, // NOON
    config.isMidnight, // MIDNIGHT
    config.isOClock, // O' CLOCK
    config.isMorning || config.isAfternoon || config.isEvening, // IN THE
    config.isMorning, // MORNING
    config.isAfternoon, // AFTERNOON
    config.isEvening, // EVENING
  ];
}

function speak (text) {
  const synth = window.speechSynthesis;
  const rate = 0.7;
  const pitch = 0.6;
  const voice = synth.getVoices().filter(v => v.lang === 'en-GB')[0];
  const utterance = new SpeechSynthesisUtterance(text);
  utterance.voice = voice;
  utterance.pitch = pitch;
  utterance.rate = rate;
  synth.speak(utterance);
}

function useClock () {
  const [timer, setTimer] = React.useState(null);
  const [time, setTime] = React.useState(getNow());

  React.useEffect(() => {
    if (!timer) initTimer();
    return (() => (timer && window.clearInterval(timer) && setTimer(null)));
  }, [timer]);

  function initTimer () {
    const now = Date.now();
    const nextSec = (Math.floor(now / 1000) + 1) * 1000;
    const timeLeft = nextSec - now;

    window.setTimeout(() => {
      const interval = window.setInterval(() => setTime(getNow()), 1000);
      setTimer(interval);
    }, timeLeft);
  }

  return time;
}

function StandardClock ({ time }) {
  const clockMarks = [ 'XII', 'I', 'II', 'III', 'IV', 'V', 'VI', 'VII', 'VIII', 'IX', 'X', 'XI' ];
  const hourAngle = ((time.hour % 12) * 60 + time.minute) / 2;
  const minuteAngle = (time.minute * 60 + time.second) / 10;
  const secondAngle = time.second * 6;

  return (
    <div className='standard-clock'>
      <div>
        { clockMarks.map(mark => <span className='mark'>{mark}</span>) }
      </div>
      <div>
        { Array(60).fill(1).map(tick => <span className='tick' />) }
      </div>
      <div className='inner-circle' />
      <div className='inner-circle-2' />
      <div className='hour-hand' style={{ transform: `rotate(${hourAngle}deg)` }} />
      <div className='minute-hand' style={{ transform: `rotate(${minuteAngle}deg)` }} />
      <div className='second-hand' style={{ transform: `rotate(${secondAngle}deg)` }} />
      <div className='center' />
    </div>
  );
}

function Speaker ({ active, text }) {
  if (!window.speechSynthesis) return null;
  React.useEffect (() => {
    if (active) speak(text);
  });
  return null;
}

function TimeReadout ({ time }) {
  const readoutConfig = getReadoutConfig(time);
  const highlighted = getHighlights(readoutConfig);
  const timeText = phrases.filter((phrase, index) => highlighted[index]).join(' ') + '.';
  const shouldSpeak = time.second === 0 && time.minute % 15 === 0;

  return (
    <div className='readout'>
      <p className='phrases'>
        { phrases.map((phrase, index) => (
          <span className={highlighted[index] ? 'glow' : ''}>
            {phrase}
          </span>
        ))}
      </p>
      <p className='timer'>{time.display}</p>
      <Speaker active={shouldSpeak} text={timeText} />
    </div>
  );
}

function NeonClock () {
  const time = useClock();
  return (
    <div className='clock'>
      <StandardClock time={time} />
      <TimeReadout time={time} />
    </div>
  );
}

const root = document.getElementById('root');
ReactDOM.render(<NeonClock />, root);