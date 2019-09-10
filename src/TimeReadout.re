// module TimeReadout = {
//   [@react.component]
//   let make = time => {
//     let readoutConfig = Config.getReadoutConfig(time);
//     // let highlighted = getHighlights(readoutConfig);
//     // let timeText = phrases->Belt.Array.mapWithIndex(phrase, index) => highlighted[index]).join(' ') + '.';
//     let shouldSpeak = time.second === 0 && time.minute % 15 === 0;

//     <div className="readout">
//       <p className="phrases">
//         {phrases->Belt.Array.mapWithIndex((phrase, index) =>
//            <span className={highlighted[index] ? "glow" : ""}>
//              phrase->React.string
//            </span>
//          )}
//       </p>
//       <p className="timer"> time.display->React.string </p>
//       <Speaker active=shouldSpeak text=timeText />
//     </div>;
//   };
// };