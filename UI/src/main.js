import Vue from 'vue'
import App from './App.vue'
var VueCookie = require('vue-cookie');

export const serverBus = new Vue();
Vue.use(VueCookie);

Vue.config.productionTip = false

new Vue({
  render: h => h(App)
}).$mount('#app')
