/*** This causes the voices to load */
let x = [%bs.raw {|(window.speechSynthesis && speechSynthesis.getVoices())|}];

let speak: (string, unit => unit) => unit =
  [@bs]
  [%bs.raw
    {|
  function(text, done) {
    console.log('speaking', text)
    speechSynthesis.cancel()
    var u = new SpeechSynthesisUtterance(text.slice(0, 500));
    var voiceName = 'Google UK English Female'
    voiceName = 'Google US English'
    u.voice = speechSynthesis.getVoices().filter(s => s.voiceURI === voiceName)[0]
    /* u.rate = 0.8 */
    var called = false
    var interval = setInterval(() => {
      if (called) return
      if (!speechSynthesis.speaking) {
        console.log('timeout')
        u.onend()
      }
    }, 50)
    var pauser = setInterval(() => {
      speechSynthesis.pause()
      speechSynthesis.resume()
    }, 10 * 1000)
    u.onend = function(event) {
      if (called) return
      clearInterval(interval)
      clearInterval(pauser)
      called = true
      console.log('done')
      done()
    }
    speechSynthesis.speak(u)
  }
|}
  ];