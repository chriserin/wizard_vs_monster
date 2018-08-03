
[%bs.raw {|require('./Stat.css')|}];

let component = ReasonReact.statelessComponent("Stat");

let make = (~name, ~value, _children) => {
  ...component,
  render: self => {
    <div className="stat">
      <span className="stat-name">(ReasonReact.string(name ++ ": "))</span>
      <span className="stat-value">(ReasonReact.string(value))</span>
    </div>
  }
}
