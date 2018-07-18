<template>
<svg class="gauge" viewBox="0 0 45.032 25.0165">
  <defs>
      <linearGradient id="gradient">
          <stop stop-color="#4caf50" offset="0%"></stop>
          <stop stop-color="#ffd900" offset="50%"></stop>
          <stop stop-color="#f44336" offset="100%"></stop>
      </linearGradient>
  </defs>
  <g>
      <polyline class="gauge__target" points="22.5165 24.5165, 13.5165 22.5165, 22.5165 20.5165" :style="'transform: rotate(' + (level>800?180:level/800*180) + 'deg);'"></polyline>
      <circle style="fill: #333" r="1.95" cx="22.5165" cy="22.5165"></circle>
  </g>
  <text text-anchor="middle" font-size="5" x="22.5165" y="13" fill="#333">{{level}}</text>
  <text text-anchor="middle" font-size="2.5" x="22.5165" y="15.5165" fill="#333">Bq/m³</text>
  <circle class="gauge__line" cx="22.5165" cy="22.5165" r="15.924" stroke-width="3.185" stroke-dasharray="0 50 50 0" fill="none"></circle>
</svg>
</template>

<script>
export default {
  props: [
    'level',
  ],
  
}
</script>

<style>
.gauge {
  shape-rendering: geometricPrecision;
  width: 100%;
  margin: auto;
  display: block;
  min-width: 100px;
  max-width: 300px;
}

.gauge__line {
  stroke: url(#gradient);
}

.gauge__target {
  -webkit-transform-origin: 22.5165px 22.5165px;
          transform-origin: 22.5165px 22.5165px;
  transition: all .5s ease;
  fill: #333;
}
</style>
