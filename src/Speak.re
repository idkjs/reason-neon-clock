external castToUtterance: 'a => SpeechSynthesis.Utterance.t = "%identity";
let speak = text => {
  let synth = SpeechSynthesis.Utterance.create("synth");
  let rate: float = 0.7;
  let pitch: float = 0.6;
  // let voice = SpeechSynthesis.getVoices();
  let voices = SpeechSynthesis.x;
  // let voices = SpeechSynthesis.getVoices();
  let getVoice = arr => arr->Belt.Array.keep(voice => voice##lang == "en-GB");
  let voice = getVoice(voices)->castToUtterance;
  let utterance = SpeechSynthesis.Utterance.set_text(text);
  let voice = SpeechSynthesis.Utterance.set_voice(voice);
  let pitch = SpeechSynthesis.Utterance.set_pitch(pitch->castToUtterance);
  let rate = SpeechSynthesis.Utterance.set_rate(rate->castToUtterance);
  let speak = SpeechSynthesis.speak(text);
  // utterance;voice; pitch;rate; speak;
  (utterance, voice, pitch, rate, speak);
  // synth.speak(utterance)
};
module Speaker = {
  [@react.component]
  let make = (active, text) => {
    React.useEffect1(
      () => {
        if (active) {
          SpeechSynthesis.speak(text);
        };
        None;
      },
      [|active|] // Here we are listing dependency on which component will be re-rendered.
    );
    <div />
  };
};