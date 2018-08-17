(function ($) {
  Drupal.behaviors.loyalist = {
    attach: function (context, settings) {
      if ('loyalist' in settings) {
        let $cooldown = settings.loyalist.cooldown;
        let $interval = settings.loyalist.interval;
        let $visits = settings.loyalist.visits;

        if ($cooldown > 0 && $interval > 0 && $visits > 0) {
          let $now = new Date();

          // Load existing log for user.
          let $log = localStorage.getItem('loyalist_log');
          if ($log != null) {
            $log = JSON.parse($log);
          }
          else {
            $log = []
          }

          // Decide if this counts as a new "visit".
          if ($log.length > 0) {
            let $last_visit = new Date($log[$log.length - 1]);
            if (($now - $last_visit)/1000 <= $cooldown) {
              return;
            }
          }

          // Prune expired visits from the log.
          $log.forEach(function(value, index){
            if (($now - new Date(value))/1000 > $interval) {
              $log.splice(index, 1);
            }
          });

          // Add current visit date to log.
          $log.push($now);

          // Set loyalist status and invoke rules.
          if ($log.length >= $visits) {
            let $status = localStorage.getItem('loyalist_loyalist');

            if ($status != null && $status === '1') {
              $.get(settings.basePath + 'loyalist/init/returning');
            }
            else {
              localStorage.setItem('loyalist_loyalist', '1');
              $.get(settings.basePath + 'loyalist/init/new');
            }
          }
          else {
            localStorage.setItem('loyalist_loyalist', '0');
            $.get(settings.basePath + 'loyalist/init/non');
          }

          // Store log (up to a maximum of $visits).
          localStorage.setItem(
            'loyalist_log',
            JSON.stringify($log.slice(-$visits))
          );
        }
      }
    }
  };
}(jQuery));
